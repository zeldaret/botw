#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

// FIXME
class SaveMgr {
    SEAD_SINGLETON_DISPOSER(SaveMgr)
    SaveMgr();
    virtual ~SaveMgr();

public:
    struct InitArg {
        sead::Heap* heap;
        u32 _8;
        u32 buf_size;
        u32 buf_alignment;
        u32 size2;
        u32 thread_priority;
        u32 _1c;
        sead::CoreIdMask thread_affinity;
        sead::SafeString save_common_str = "save_common";
        sead::SafeString save_act_str = "save_act";
        bool is_demo = false;
        sead::SafeString save_rid_demo_dir;
        void* _60 = nullptr;
        u32 _68 = 0;
        u32 _6c;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x70);

    void init(const InitArg& arg);
    void loadGameSaveData();
};

}  // namespace ksys
