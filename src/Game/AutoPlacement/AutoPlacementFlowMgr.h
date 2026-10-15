#pragma once

#include <container/seadObjArray.h>
#include <container/seadSafeArray.h>
#include <evfl/Flowchart.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"

namespace uking {

class AutoPlacement;

struct AutoPlacementFlowRes {
    ~AutoPlacementFlowRes();

    bool load(int resource_idx, sead::Heap* heap);
    void initActionAndQueryHandlers();
    void start(AutoPlacement* placement, const char* unit_name, const u16* spawn_location_flags);

    ksys::res::Handle handle;
    sead::SafeString evfl_name;
    evfl::FlowchartContext flowchart_ctx;
    AutoPlacement* placement = nullptr;
    sead::SafeString unit_name;
    u8 idx = 0xFF;
    s8 placement_type = 0;
    u16 spawn_location_flags = 0;
    sead::FixedObjArray<sead::SafeString, 32> actor_names;
};

KSYS_CHECK_SIZE_NX150(AutoPlacementFlowRes, 0x430);

class AutoPlacementFlowMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementFlowMgr)
public:
    AutoPlacementFlowMgr();
    ~AutoPlacementFlowMgr();

    void loadEventFlows();
    bool resAreReady();

    AutoPlacementFlowRes* getFlow(const sead::SafeString& actor_name, bool near_flow);

private:
    sead::Heap* mHeap;
    sead::SafeArray<AutoPlacementFlowRes, 10> mFlowArray;
    sead::SafeArray<AutoPlacementFlowRes, 7> mFlowNearArray;
};

KSYS_CHECK_SIZE_NX150(AutoPlacementFlowMgr, 0x4758);

}  // namespace uking
