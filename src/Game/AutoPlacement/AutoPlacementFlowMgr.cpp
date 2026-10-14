#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"
#include <container/seadBuffer.h>
#include <evfl/ResActor.h>
#include <evfl/ResEventFlowFile.h>
#include <evfl/ResFlowchart.h>
#include <resource/seadResource.h>
#include "Game/AutoPlacement/AutoPlacement.h"
#include "Game/AutoPlacement/AutoPlacementFlowInterfaces.h"
#include "KingSystem/Resource/resLoadRequest.h"

namespace uking {

const char* sFlowResNamesData[] = {
    "AutoPlacement_Animal.bfevfl",
    "AutoPlacement_Bird.bfevfl",
    "AutoPlacement_Enemy_Golem_Little.bfevfl",
    "AutoPlacement_Enemy_Keese.bfevfl",
    "AutoPlacement_Enemy_Lizalfos.bfevfl",
    "AutoPlacement_Enemy_Octarock.bfevfl",
    "AutoPlacement_Enemy_Wizzrobe.bfevfl",
    "AutoPlacement_Fish.bfevfl",
    "AutoPlacement_Insect.bfevfl",
    "AutoPlacement_Material.bfevfl",
};
sead::Buffer<const char*> sFlowResNames{sFlowResNamesData};

const char* sFlowNearResNamesData[] = {
    "AutoPlacementNear_Enemy_Assassin_Middle.bfevfl",
    "AutoPlacementNear_Enemy_Assassin_Shooter_Junior.bfevfl",
    "AutoPlacementNear_Enemy_Chuchu.bfevfl",
    "AutoPlacementNear_Enemy_Dragon.bfevfl",
    "AutoPlacementNear_Enemy_Lizalfos.bfevfl",
    "AutoPlacementNear_Enemy_Octarock.bfevfl",
    "AutoPlacementNear_Enemy_Stal.bfevfl",
};
sead::Buffer<const char*> sFlowNearResNames{sFlowNearResNamesData};

void AutoPlacementFlowMgr::loadEventFlows() {
    for (int i = 0; i < mFlowArray.size(); i++) {
        auto& flow = mFlowArray[i];
        flow.evfl_name = sFlowResNames[i];
        flow.idx = 0xFF;

        sead::FixedSafeString<128> path;
        path.format("EventFlow/%s", flow.evfl_name.cstr());
        ksys::res::LoadRequest req;
        req.mRequester = "AutoPlacementFlow";

        flow.handle.requestLoad(path, &req);
    }

    for (int i = 0; i < mFlowNearArray.size(); i++) {
        auto& flow = mFlowNearArray[i];
        flow.evfl_name = sFlowNearResNames[i];
        flow.idx = 0xFF;

        sead::FixedSafeString<128> path;
        path.format("EventFlow/%s", flow.evfl_name.cstr());
        ksys::res::LoadRequest req;
        req.mRequester = "AutoPlacementFlow";

        flow.handle.requestLoad(path, &req);
    }
}

AutoPlacementFlowRes* AutoPlacementFlowMgr::getFlow(const sead::SafeString& actor_name,
                                                    bool near_flow) {
    AutoPlacementFlowRes* flows = mFlowArray.getBufferPtr();
    u32 num_flows = mFlowArray.size();
    if (near_flow) {
        flows = mFlowNearArray.getBufferPtr();
        num_flows = mFlowNearArray.size();
    }
    for (u32 i = 0; i != num_flows; ++i) {
        auto& flow = flows[i];
        for (const auto& name : flow.actor_names) {
            if (name == actor_name)
                return &flow;
        }
    }
    return nullptr;
}

bool AutoPlacementFlowMgr::resAreReady() {
    for (int i = 0; i < mFlowArray.size(); ++i) {
        if (!mFlowArray[i].load(i, mHeap))
            return false;
    }
    for (int i = 0; i < mFlowNearArray.size(); ++i) {
        if (!mFlowNearArray[i].load(i, mHeap))
            return false;
    }
    return true;
}

static const sead::SafeString sActorName{"ActorName"};

static void* autoPlacementBfevflAlloc(size_t size, size_t alignment, void* userdata) {
    return static_cast<sead::Heap*>(userdata)->alloc(size, s32(alignment));
}

static void autoPlacementBfevflFree(void* ptr, void* userdata) {
    static_cast<sead::Heap*>(userdata)->free(ptr);
}

// NON_MATCHING: compiler global layout and loop code generation differ.
bool AutoPlacementFlowRes::load(int resource_idx, sead::Heap* heap) {
    if (s8(idx) >= 0 || handle.checkLoadStatus())
        return true;
    if (!handle.isReadyOrNeedsParse())
        return false;

    handle.parseResource(nullptr);
    idx = resource_idx;
    if (evfl_name.findIndex("Animal") != -1)
        placement_type = 1;
    else if (evfl_name.findIndex("Bird") != -1)
        placement_type = 4;
    else if (evfl_name.findIndex("Fish") != -1)
        placement_type = 3;
    else if (evfl_name.findIndex("Insect") != -1)
        placement_type = 2;
    else if (evfl_name.findIndex("Material") != -1)
        placement_type = 5;
    else
        placement_type = 0;

    auto* resource = sead::DynamicCast<sead::DirectResource>(handle.getResource());
    if (resource && evfl::ResEventFlowFile::IsValid(resource->getRawData())) {
        const auto* file = evfl::ResEventFlowFile::ResCast(resource->getRawData());
        const auto* flowchart = file->flowcharts.Get()->Get();
        const evfl::ResFlowchart* flowcharts[] = {flowchart};
        evfl::FlowchartContext::Builder builder{{flowcharts, 1}};
        if (builder.SetEntryPoint(*flowchart->name.Get(), "EntryPoint0")) {
            builder.Build(&flowchart_ctx,
                          {autoPlacementBfevflAlloc, autoPlacementBfevflFree, heap, heap});
            initActionAndQueryHandlers();
            const u32 num_events = flowchart->num_events;
            const auto* events = flowchart->events.Get();
            for (u32 i = 0; i < num_events; ++i) {
                const auto& event = events[i];
                if (event.type == evfl::ResEvent::EventType::kSwitch && event.params.Get()) {
                    const auto* metadata = event.params.Get()->Get(
                        sActorName.cstr(), ore::ResMetaData::DataType::kString);
                    if (metadata && !actor_names.isFull())
                        actor_names.emplaceBack(metadata->value.str.Get()->data());
                }
            }
        }
    }
    return true;
}

void AutoPlacementFlowRes::start(AutoPlacement* placement, const char* unit_name,
                                 const u16* spawn_location_flags) {
    this->unit_name = unit_name;
    this->spawn_location_flags = *spawn_location_flags;
    this->placement = placement;
    if (flowchart_ctx.IsInitialized())
        flowchart_ctx.Start(nullptr);
}

namespace {

bool namesEqual(const ore::StringView& lhs, const ore::StringView& rhs) {
    return lhs.size() == rhs.size() && compareStringViews(lhs, rhs) == 0;
}

}  // namespace

static ore::StringView sGroundNorm{"GroundNorm"};
static ore::StringView sGroundMat{"GroundMat"};
static ore::StringView sTreeRate{"TreeRate"};
static ore::StringView sPosHeight{"PosHeight"};
static ore::StringView sWaterDepth{"WaterDepth"};
static ore::StringView sRouteDistance{"RouteDistance"};
static ore::StringView sGrassHeight{"GrassHeight"};
static ore::StringView sWaterSurface{"WaterSurface"};
static ore::StringView sPlayerRideHorse{"PlayerRideHorse"};
static ore::StringView sEcoAreaActorName{"EcoAreaActorName"};
static ore::StringView sWaterSubMat{"WaterSubMat"};
static ore::StringView sCheckGameData{"CheckGameData"};
static ore::StringView sCheckPouchItemCount{"CheckPouchItemCount"};
static ore::StringView sCheckPouchItemCountFromActor{"CheckPouchItemCountFromActor"};
static ore::StringView sTimeType{"TimeType"};
static ore::StringView sRailDistance{"RailDistance"};
static ore::StringView sWaterDistance{"WaterDistance"};
static ore::StringView sNavMeshFace{"NavMeshFace"};
static ore::StringView sCreateData{"CreateData"};
static ore::StringView sNearCreate{"NearCreate"};
static ore::StringView sAppearWeatherRate{"AppearWeatherRate"};
static ore::StringView sEquipCategory{"EquipCategory"};

namespace AutoPlacementFlowHandlers {

void nearCreate(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler) {
    int wait_frame;
    if (arg.param_accessor.FindInt(&wait_frame, "WaitFrame")) {
        auto* flow = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data);
        flow->placement->setNearCreateWaitFrame(u16(wait_frame));
    }
    done_handler.Invoke();
}

void equipCategory(const evfl::ActionArg& arg, evfl::ActionDoneHandler done_handler) {
    auto* flow = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data);
    auto* placement = flow->placement;
    int category = -1;
    if (arg.param_accessor.FindInt(&category, "Category"))
        placement->setEquipCategory(category);
    done_handler.Invoke();
}

void defaultAction(const evfl::ActionArg&, evfl::ActionDoneHandler done_handler) {
    done_handler.Invoke();
}

int defaultQuery(const evfl::QueryArg&) {
    return 0;
}

}  // namespace AutoPlacementFlowHandlers

// NON_MATCHING: external handler references use GOT addressing; compiler allocation differs.
void AutoPlacementFlowRes::initActionAndQueryHandlers() {
    evfl_name.cstr();
    for (auto obj = flowchart_ctx.GetObjs().begin(); obj != flowchart_ctx.GetObjs().end(); ++obj) {
        for (auto actor = obj->GetActBinder().GetBindings().begin();
             actor != obj->GetActBinder().GetBindings().end(); ++actor) {
            if (actor->IsUsed() && !actor->IsInitialized()) {
                actor->SetUserData(this);
                actor->SetInitialized(true);
            }
        }
    }

    for (auto obj = flowchart_ctx.GetObjs().begin(); obj != flowchart_ctx.GetObjs().end(); ++obj) {
        for (auto actor = obj->GetActBinder().GetBindings().begin();
             actor != obj->GetActBinder().GetBindings().end(); ++actor) {
            if (!actor->IsUsed() || !actor->IsInitialized())
                continue;
            for (auto action = actor->GetActions().begin(); action != actor->GetActions().end();
                 ++action) {
                const auto* resource_action = action->res_action;
                if (namesEqual(sCreateData, *resource_action->name.Get()))
                    action->handler = AutoPlacementFlowHandlers::createData;
                else if (namesEqual(sNearCreate, *resource_action->name.Get()))
                    action->handler = AutoPlacementFlowHandlers::nearCreate;
                else if (namesEqual(sAppearWeatherRate, *resource_action->name.Get()))
                    action->handler = AutoPlacementFlowHandlers::appearWeatherRate;
                else if (namesEqual(sEquipCategory, *resource_action->name.Get()))
                    action->handler = AutoPlacementFlowHandlers::equipCategory;
                else
                    action->handler = AutoPlacementFlowHandlers::defaultAction;
                action->user_data = nullptr;
            }
        }
    }

    for (auto obj = flowchart_ctx.GetObjs().begin(); obj != flowchart_ctx.GetObjs().end(); ++obj) {
        for (auto actor = obj->GetActBinder().GetBindings().begin();
             actor != obj->GetActBinder().GetBindings().end(); ++actor) {
            if (!actor->IsUsed() || !actor->IsInitialized())
                continue;
            for (auto query = actor->GetQueries().begin(); query != actor->GetQueries().end();
                 ++query) {
                const auto* resource_query = query->res_query;
                if (namesEqual(sGroundNorm, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::groundNorm;
                else if (namesEqual(sGroundMat, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::groundMat;
                else if (namesEqual(sTreeRate, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::treeRate;
                else if (namesEqual(sPosHeight, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::posHeight;
                else if (namesEqual(sWaterDepth, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::waterDepth;
                else if (namesEqual(sRouteDistance, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::routeDistance;
                else if (namesEqual(sGrassHeight, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::grassHeight;
                else if (namesEqual(sWaterSurface, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::waterSurface;
                else if (namesEqual(sPlayerRideHorse, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::playerRideHorse;
                else if (namesEqual(sEcoAreaActorName, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::ecoAreaActorName;
                else if (namesEqual(sWaterSubMat, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::waterSubMat;
                else if (namesEqual(sCheckGameData, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::checkGameData;
                else if (namesEqual(sCheckPouchItemCount, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::checkPouchItemCount;
                else if (namesEqual(sCheckPouchItemCountFromActor, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::checkPouchItemCountFromActor;
                else if (namesEqual(sTimeType, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::timeType;
                else if (namesEqual(sRailDistance, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::railDistance;
                else if (namesEqual(sWaterDistance, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::waterDistance;
                else if (namesEqual(sNavMeshFace, *resource_query->name.Get()))
                    query->handler = AutoPlacementFlowHandlers::navMeshFace;
                else
                    query->handler = AutoPlacementFlowHandlers::defaultQuery;
                query->user_data = nullptr;
            }
        }
    }
}

}  // namespace uking
