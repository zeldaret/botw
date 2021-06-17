#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"

namespace al {
class ByamlIter;
}

namespace evfl {
struct ResEventFlowFile;
struct ResTimeline;
class TimelineObj;
}  // namespace evfl

namespace ksys::evt {

class ActorBindings;

class ResourceTimeline {
public:
    ResourceTimeline();
    virtual ~ResourceTimeline();

    /// Loads event timeline resource files asynchronously.
    void loadEventFlow(sead::Heap* heap, const al::ByamlIter& event_info, res::Handle* pack_handle);

    /// @return true if the load completed (succeeded or failed), false if it is still ongoing.
    bool finishLoad();

    /// @return whether at least one actor was bound.
    bool setUpBindings(ActorBindings* bindings, sead::Heap* heap);

    /// @return whether the build was successful.
    bool buildTimeline(evfl::TimelineObj* obj, int idx, sead::Heap* heap);

private:
    struct Res {
        res::Handle handle;
        const evfl::ResEventFlowFile* res_event_flow_file;
        const evfl::ResTimeline* res_timeline;
        bool loaded;
    };

    sead::Buffer<Res> mTimelines;
    bool mLoadFailed;
    sead::FixedSafeString<64> mName;
};

}  // namespace ksys::evt
