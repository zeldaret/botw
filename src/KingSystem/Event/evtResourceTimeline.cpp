#include "KingSystem/Event/evtResourceTimeline.h"
#include <evfl/ResEventFlowFile.h>
#include <evfl/ResTimeline.h>
#include <evfl/TimelineObj.h>
#include "KingSystem/Event/evtActorBindings.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Resource/Event/resEventFlowBinder.h"
#include "KingSystem/Resource/Event/resResourceEventFlow.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::evt {

ResourceTimeline::ResourceTimeline() {
    mLoadFailed = false;
}

ResourceTimeline::~ResourceTimeline() {
    for (int i = 0; i < mTimelines.size(); ++i)
        mTimelines[i].handle.requestUnload2();

    mTimelines.freeBuffer();
}

void ResourceTimeline::loadEventFlow(sead::Heap* heap, const al::ByamlIter& event_info,
                                     res::Handle* pack_handle) {
    al::ByamlIter sub_timelines;
    int num_sub_timelines = 0;
    if (event_info.tryGetIterByKey(&sub_timelines, "sub_timelines"))
        num_sub_timelines = sub_timelines.getSize();

    res::LoadRequest request;
    request.mRequester = "ResourceTimeline";
    request.mPackHandle = pack_handle;
    request._22 = true;

    mTimelines.allocBufferAssert(1 + num_sub_timelines, heap);

    for (int i = 0; i < mTimelines.size(); ++i)
        mTimelines[i].loaded = false;

    // Load the main flowchart.
    sead::FormatFixedSafeString<128> path("EventFlow/%s.bfevtm", mName.cstr());
    mTimelines[0].handle.requestLoad(path, &request);

    // Load any subfiles.
    for (int i = 0; i < num_sub_timelines; ++i) {
        al::ByamlIter sub_entry;
        sub_timelines.tryGetIterByIndex(&sub_entry, i);
        const char* sub_timeline_name;
        sub_entry.tryGetStringByKey(&sub_timeline_name, "name");

        sead::FormatFixedSafeString<128> sub_path("EventFlow/%s.bfevtm", sub_timeline_name);
        mTimelines[i + 1].handle.requestLoad(sub_path, &request);
    }
}

bool ResourceTimeline::finishLoad() {
    bool ready = true;

    for (int i = 0; i < mTimelines.size(); ++i) {
        auto& timeline = mTimelines[i];
        if (timeline.loaded)
            continue;

        if (timeline.handle.isReadyOrNeedsParse())
            timeline.handle.parseResource(nullptr);

        if (timeline.handle.isSuccess()) {
            auto* evfl_res = sead::DynamicCast<res::EventTimeline>(timeline.handle.getResource());
            if (evfl_res) {
                timeline.res_event_flow_file = evfl_res->getRes();
                timeline.res_timeline = timeline.res_event_flow_file->timelines.Get()->Get();
                timeline.loaded = true;
            }
        } else if (timeline.handle.checkLoadStatus()) {
            timeline.loaded = true;
            mLoadFailed = true;
        }

        if (!timeline.loaded)
            ready = false;
    }

    return ready;
}

long bindActorActions(evfl::TimelineObj& obj, res::EventFlowActionBinder binder) {
    auto* res_timeline = obj.GetTimeline();

    ore::Array<const evfl::ResActor> actors{res_timeline->actors.Get(), res_timeline->num_actors};
    for (int actor_idx = 0; actor_idx < actors.size(); ++actor_idx) {
        ore::Array<const evfl::ResAction> actions{actors[actor_idx].actions.Get(),
                                                  actors[actor_idx].num_actions};
        for (int i = 0; i < actions.size(); ++i)
            obj.GetActBinder().RegisterAction(actor_idx, &actions[i]);
    }

    u8 ok;
    u8 failed;
    auto binder_ = binder;

    ok = false;
    failed = false;

    auto& evfl_bindings = obj.GetActBinder().GetBindings();
    for (auto b = evfl_bindings.begin(); b != evfl_bindings.end(); ++b) {
        if (!b->IsUsed() || !b->IsInitialized())
            continue;

        const auto* actor = b->GetActor();
        for (auto a = b->GetActions().begin(); a != b->GetActions().end(); ++a) {
            binder_.bind(a, a->res_action, actor, static_cast<ActorBinding*>(b->GetUserData()));
            (a->handler ? ok : failed) = true;
        }
    }

    return int(ok) | (int(failed) << 8);
}

// NON_MATCHING: minor reordering for the buildTimeline loop
bool ResourceTimeline::setUpBindings(ActorBindings* bindings, sead::Heap* heap) {
    sead::Buffer<evfl::TimelineObj> timeline_objs;
    timeline_objs.allocBufferAssert(mTimelines.size(), heap);

    [&] {
        for (int i = 0; i < mTimelines.size(); ++i)
            buildTimeline(&timeline_objs[i], i, heap);
    }();

    // Bind actors. (For an explanation of why binding is done twice, see ResourceFlowchart.)
    const auto bind_actors = [&] {
        for (int i = 0; i < mTimelines.size(); ++i) {
            auto& obj = timeline_objs[i];
            res::EventFlowActorBinder binder(bindings, heap);
            bool ok = false;
            bool failed = false;

            auto& evfl_bindings = obj.GetActBinder().GetBindings();
            for (auto it = evfl_bindings.begin(); it != evfl_bindings.end(); ++it) {
                if (it->IsUsed() && !it->IsInitialized()) {
                    binder.bind(it, it->GetActor());
                    (it->IsInitialized() ? ok : failed) = true;
                }
            }
        }
    };
    bind_actors();
    bindings->allocBindings(heap);
    bind_actors();

    // Bind actions.
    for (int i = 0; i < mTimelines.size(); ++i)
        bindActorActions(timeline_objs[i], res::EventFlowActionBinder(bindings, heap));
    bindings->allocBindingsActions(heap);
    for (int i = 0; i < mTimelines.size(); ++i)
        bindActorActions(timeline_objs[i], res::EventFlowActionBinder(bindings, heap));

    for (int i = 0; i < mTimelines.size(); ++i)
        timeline_objs[i].GetActBinder().UnbindAll();

    timeline_objs.freeBuffer();
    return true;
}

bool ResourceTimeline::buildTimeline(evfl::TimelineObj* obj, int idx, sead::Heap* heap) {
    auto& timeline = mTimelines[idx];
    evfl::TimelineObj::Builder builder(timeline.res_timeline);
    return builder.Build(obj, makeEvflAllocateArg(heap));
}

}  // namespace ksys::evt
