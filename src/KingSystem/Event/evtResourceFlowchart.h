#pragma once

#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"

namespace evfl {
class FlowchartContext;
struct ResEventFlowFile;
struct ResFlowchart;
}  // namespace evfl

namespace ksys::evt {

class ActorBindings;

class ResourceFlowchart {
public:
    ResourceFlowchart();
    virtual ~ResourceFlowchart();

    /// Loads event flowchart resource files asynchronously.
    void loadEventFlow(sead::Heap* heap, res::Handle* pack_handle);

    /// @return true if the load completed (succeeded or failed), false if it is still ongoing.
    bool finishLoad();

    /// @return whether at least one actor was bound.
    bool setUpBindings(ActorBindings* bindings, sead::Heap* heap);

    /// @return whether the build was successful.
    bool buildFlowchart(evfl::FlowchartContext* context, sead::Heap* heap);

    bool isResourceLoaded(const sead::SafeString& path_substring) const;

private:
    struct Res {
        res::Handle handle;
        const evfl::ResEventFlowFile* res_event_flow_file;
        const evfl::ResFlowchart* res_flowchart;
        bool loaded;
    };

    sead::Buffer<Res> mFlowcharts;
    sead::Buffer<Res> mMissingFlowcharts;
    bool mLoadFailed;
    sead::FixedSafeString<64> mName;
    sead::FixedSafeString<128> mEntryPoint;
};

}  // namespace ksys::evt
