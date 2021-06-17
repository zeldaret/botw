#include "KingSystem/Event/evtResourceFlowchart.h"
#include <array>
#include <evfl/Flowchart.h>
#include <evfl/ResEventFlowFile.h>
#include "KingSystem/Event/evtActorBindings.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtInfoData.h"
#include "KingSystem/Resource/Event/resEventFlowBinder.h"
#include "KingSystem/Resource/Event/resResourceEventFlow.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::evt {

ResourceFlowchart::ResourceFlowchart() {
    mLoadFailed = false;
}

ResourceFlowchart::~ResourceFlowchart() {
    for (int i = 0; i < mFlowcharts.size(); ++i)
        mFlowcharts[i].handle.requestUnload2();

    mFlowcharts.freeBuffer();

    if (mMissingFlowcharts.isBufferReady()) {
        for (int i = 0; i < mFlowcharts.size(); ++i)
            mMissingFlowcharts[i].handle.requestUnload2();

        mMissingFlowcharts.freeBuffer();
    }
}

void ResourceFlowchart::loadEventFlow(sead::Heap* heap, res::Handle* pack_handle) {
    al::ByamlIter event_info;
    al::ByamlIter subfiles;
    int num_flowcharts = 1;
    if (InfoData::instance()->getEntry(&event_info, mName, mEntryPoint) &&
        event_info.tryGetIterByKey(&subfiles, "subfile")) {
        num_flowcharts = subfiles.getSize() + 1;
    }

    mFlowcharts.allocBufferAssert(num_flowcharts, heap);

    res::LoadRequest request;
    request.mRequester = "ResourceFlowchart";
    request.mPackHandle = pack_handle;
    request._22 = true;

    // Load the main flowchart.
    sead::FixedSafeString<128> path;
    mFlowcharts[0].loaded = false;
    path.format("EventFlow/%s.bfevfl", mName.cstr());
    mFlowcharts[0].handle.requestLoad(path, &request);

    // Load any subfiles.
    for (int i = 1; i < num_flowcharts; ++i) {
        al::ByamlIter file_entry;
        subfiles.tryGetIterByIndex(&file_entry, i - 1);
        const char* file_name;
        file_entry.tryGetStringByKey(&file_name, "file");

        mFlowcharts[i].loaded = false;
        path.format("EventFlow/%s", file_name);
        mFlowcharts[i].handle.requestLoad(path, &request);
    }
}

bool ResourceFlowchart::finishLoad() {
    bool ready = true;

    for (int i = 0; i < mFlowcharts.size(); ++i) {
        auto& flowchart = mFlowcharts[i];
        if (flowchart.loaded)
            continue;

        if (flowchart.handle.isReadyOrNeedsParse())
            flowchart.handle.parseResource(nullptr);

        if (flowchart.handle.isSuccess()) {
            auto* evfl_res = sead::DynamicCast<res::EventFlowchart>(flowchart.handle.getResource());
            if (evfl_res) {
                flowchart.res_event_flow_file = evfl_res->getRes();
                flowchart.res_flowchart = flowchart.res_event_flow_file->flowcharts.Get()->Get();
                flowchart.loaded = true;
            }
        } else if (flowchart.handle.checkLoadStatus()) {
            flowchart.loaded = true;
            mLoadFailed = true;
        }

        if (!flowchart.loaded)
            ready = false;
    }

    return ready;
}

long bindActorActions(evfl::FlowchartContext& context, res::EventFlowActionBinder binder) {
    u8 any_ok = 0;
    u8 any_failed = 0;

    for (auto it = context.GetObjs().begin(); it != context.GetObjs().end(); ++it) {
        bool ok;
        bool failed;
        auto binder_ = binder;

        ok = false;
        failed = false;

        auto& evfl_bindings = it->GetActBinder().GetBindings();
        for (auto b = evfl_bindings.begin(); b != evfl_bindings.end(); ++b) {
            if (!b->IsUsed() || !b->IsInitialized())
                continue;

            const auto* actor = b->GetActor();
            for (auto a = b->GetActions().begin(); a != b->GetActions().end(); ++a) {
                binder_.bind(a, a->res_action, actor, static_cast<ActorBinding*>(b->GetUserData()));
                (a->handler ? ok : failed) = true;
            }
        }

        if (ok)
            any_ok = 1;
        if (failed)
            any_failed = 1;
    }

    return (int(any_failed) << 8) | int(any_ok);
}

long bindActorQueries(evfl::FlowchartContext& context, res::EventFlowQueryBinder binder) {
    u8 any_ok = 0;
    u8 any_failed = 0;

    for (auto it = context.GetObjs().begin(); it != context.GetObjs().end(); ++it) {
        bool ok;
        bool failed;
        auto binder_ = binder;

        ok = false;
        failed = false;

        auto& evfl_bindings = it->GetActBinder().GetBindings();
        for (auto b = evfl_bindings.begin(); b != evfl_bindings.end(); ++b) {
            if (!b->IsUsed() || !b->IsInitialized())
                continue;

            const auto* actor = b->GetActor();
            for (auto q = b->GetQueries().begin(); q != b->GetQueries().end(); ++q) {
                binder_.bind(q, q->res_query, actor, static_cast<ActorBinding*>(b->GetUserData()));
                (q->handler ? ok : failed) = true;
            }
        }

        if (ok)
            any_ok = 1;
        if (failed)
            any_failed = 1;
    }

    return (int(any_failed) << 8) | int(any_ok);
}

bool ResourceFlowchart::setUpBindings(ActorBindings* bindings, sead::Heap* heap) {
    evfl::FlowchartContext context;
    if (!buildFlowchart(&context, heap))
        return false;

    // Bind actors. We do it twice: once in order to figure out how many actor bindings
    // need to be allocated, and a second time to actually bind actors.
    const auto bind_actors = [&] {
        for (auto it = context.GetObjs().begin(); it != context.GetObjs().end(); ++it) {
            bool ok;
            bool failed;
            res::EventFlowActorBinder binder{bindings, heap};

            ok = false;
            failed = false;

            auto& evfl_bindings = it->GetActBinder().GetBindings();
            for (auto binding = evfl_bindings.begin(); binding != evfl_bindings.end(); ++binding) {
                if (binding->IsUsed() && !binding->IsInitialized()) {
                    binder.bind(binding, binding->GetActor());
                    (binding->IsInitialized() ? ok : failed) = true;
                }
            }
        }
    };
    bind_actors();
    bindings->allocBindings(heap);
    bind_actors();

    // Bind actions.
    res::EventFlowActionBinder action_binder_1{bindings, heap};
    bindActorActions(context, action_binder_1);
    bindings->allocBindingsActions(heap);
    res::EventFlowActionBinder action_binder_2{bindings, heap};
    bindActorActions(context, action_binder_2);

    // Bind queries.
    res::EventFlowQueryBinder query_binder_1{bindings, heap};
    bindActorQueries(context, query_binder_1);
    bindings->allocBindingsQueries(heap);
    res::EventFlowQueryBinder query_binder_2{bindings, heap};
    bindActorQueries(context, query_binder_2);

    context.UnbindAll();

    return bindings->getNumBindings() != 0;
}

bool ResourceFlowchart::buildFlowchart(evfl::FlowchartContext* context, sead::Heap* heap) {
    std::array<const evfl::ResFlowchart*, 32> flowcharts;
    int num_flowcharts = 0;

    const auto add_flowcharts = [&] {
        for (int i = 0; i < mFlowcharts.size(); ++i)
            flowcharts[num_flowcharts++] = mFlowcharts[i].res_flowchart;
    };
    add_flowcharts();

    evfl::FlowchartContext::Builder builder({flowcharts.data(), num_flowcharts});

    if (!builder.SetEntryPoint(mName.cstr(), mEntryPoint.cstr()))
        return false;

    evfl::FlowchartContext::Builder::BuildResult result;
    if (builder.Build(&result, context, makeEvflAllocateArg(heap)))
        return true;

    // Load any missing flowchart.
    // Note: this only works in debug builds; in release builds there is no debug heap
    // to allocate the mMissingFlowcharts buffer.
    mMissingFlowcharts.freeBuffer();
    static constexpr int NumFallbackRes = 8;
    for (int i = 0; i < NumFallbackRes; ++i) {
        if (result.result !=
            evfl::FlowchartContext::Builder::BuildResultType::kResFlowchartNotFound) {
            continue;
        }

        sead::FormatFixedSafeString<128> path("EventFlow/%s.bfevfl",
                                              result.missing_flowchart_name.data());

        if (!mMissingFlowcharts.isBufferReady())
            mMissingFlowcharts.allocBufferAssert(NumFallbackRes, util::getDebugHeap());

        res::ResourceMgrTask::instance()->controlField9c0d88(false);
        mMissingFlowcharts[i].handle.load(path, nullptr);
        res::ResourceMgrTask::instance()->controlField9c0d88(true);

        /// @bug Bug? This causes all flowcharts in mFlowcharts to be added more than once...
        add_flowcharts();

        for (int flow_idx = 0; flow_idx < i + 1; ++flow_idx) {
            auto* flowchart = sead::DynamicCast<res::EventFlowchart>(
                mMissingFlowcharts[flow_idx].handle.getResource());
            flowcharts[num_flowcharts++] = flowchart->getRes()->flowcharts.Get()->Get();
        }

        evfl::FlowchartContext::Builder builder2({flowcharts.data(), num_flowcharts});
        if (!builder2.SetEntryPoint(mName.cstr(), mEntryPoint.cstr()))
            continue;
        if (!builder2.Build(&result, context, makeEvflAllocateArg(heap)))
            continue;
        return true;
    }

    return false;
}

bool ResourceFlowchart::isResourceLoaded(const sead::SafeString& path_substring) const {
    for (int i = 0; i < mFlowcharts.size(); ++i) {
        auto* unit = mFlowcharts[i].handle.getUnit();
        if (unit && unit->getPath().include(path_substring))
            return true;
    }
    return false;
}

}  // namespace ksys::evt
