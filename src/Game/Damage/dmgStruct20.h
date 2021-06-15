#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "KingSystem/Utils/Types.h"

namespace uking::dmg {

// What exactly Struct20 is, isn't known yet.
// It is used by the Damage Managers, especially DamageManager and up, not so much in
// DamageManagerBase. It contains flags and values which seems to be returned and modified when
// handling damage.

// TODO: Figure out exactly what Struct20 does and rename struct + variables to fit.

class Struct20Base {
    SEAD_RTTI_BASE(Struct20Base)

public:
    virtual ~Struct20Base(){};

    virtual void reset();
    virtual void combineMaybe(Struct20Base* other);
};

class Struct20 : public Struct20Base {
    SEAD_RTTI_OVERRIDE(Struct20, Struct20Base)

public:
    ~Struct20() override { ; }

    void reset() override;

    __attribute__((noinline)) virtual void combineMaybe(Struct20Base* other) override;

    // Unknown which fields belong in Struct20 vs Struct20Base
    u32 mField_8 = 0;
    u32 mField_C = 0;
    s32 mField_10 = 0;
    s32 mField_14 = -1;
    s32 mField_18 = -1;
    u32 mField_1C;  // Flag of some kind
};
KSYS_CHECK_SIZE_NX150(Struct20, 0x20);

class Struct20_2 : public Struct20 {
    SEAD_RTTI_OVERRIDE(Struct20_2, Struct20)

public:
    ~Struct20_2() override { ; }

    void reset() override;
    void combineMaybe(Struct20Base* other) override;

    f32 mField_20;
    f32 mField_24;
    f32 mField_28;
    f32 mField_2C;
    bool mField_30;
};
KSYS_CHECK_SIZE_NX150(Struct20_2, 0x38);

}  // namespace uking::dmg
