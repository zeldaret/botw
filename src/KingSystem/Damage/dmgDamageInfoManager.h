#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>

#include "KingSystem/Resource/resHandle.h"

namespace ksys::dmg {

// FIXME: incomplete
class DamageInfoMgr_DamageItem {
public:
    s32 mField_0;  // unknown
    sead::SafeArray<u8, 3> mCanTakeDamageFromType;
};

// FIXME: incomplete
class DamageInfoMgr {
public:
    SEAD_SINGLETON_DISPOSER(DamageInfoMgr);

public:
    u8 TEMP1[0x5F8];                                       // Fields
    ksys::res::Handle* mReactionTable;                     // 0x5D0
    sead::Buffer<DamageInfoMgr_DamageItem> mDamagesArray;  // 0x620
};
// KSYS_CHECK_SIZE_NX150(DamageInfoMgr, 0x12F0);

}  // namespace ksys::dmg
