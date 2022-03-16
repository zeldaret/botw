#pragma once

#include <container/seadSafeArray.h>
#include <evfl/Flowchart.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"

namespace ksys::map {

class AutoPlacement;

struct AutoPlacementFlowRes {
    void start(AutoPlacement* placement, const sead::SafeString& unit_name, int*);

    res::Handle handle;
    sead::SafeString evfl_name;
    evfl::FlowchartContext flowchart_ctx;
    AutoPlacement* placement;
    sead::SafeString unit_name;
    u8 idx;
    s8 placement_type;
};

class AutoPlacementFlowMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementFlowMgr)
public:
    AutoPlacementFlowMgr();
    virtual ~AutoPlacementFlowMgr();

    void loadEventFlows();

    AutoPlacementFlowRes* getFlow(const sead::SafeString& actor_name, bool near_flow);

private:
    sead::Heap* mHeap;
    sead::SafeArray<AutoPlacementFlowRes, 10> mFlowArray;
    sead::SafeArray<AutoPlacementFlowRes, 7> mFlowNearArray;
};

}  // namespace ksys::map
