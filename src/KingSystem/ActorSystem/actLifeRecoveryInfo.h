#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

#include "KingSystem/Utils/Types.h"

namespace ksys::act {

// FIXME: incomplete
class LifeRecoverInfo {
public:
    void init(void* params);

    // Modifies extra Hp1 and Damage. (Regen?)
    bool onApplyDamage(s32& damage);

    // Update flags and counter
    void onApplyDamage_0();

    void printLifeRecoverInfo(u32 life, sead::FormatFixedSafeString<128>** Output);

    f32 mCounter;
    f32 mField_4;
    u8 gap_8[16];  // Is this really a gap?
    u32 mExtraHp1;
    u32 mExtraHp2;
    u32 mMaxLife;
    f32 mRecoverFactor;
    s32 mField_28;
    f32 mField_2C;
    u8 mFlags;
    u8 mUnknown[7];  // Flags might just be two u32
};
KSYS_CHECK_SIZE_NX150(LifeRecoverInfo, 0x38);

}  // namespace ksys::act
