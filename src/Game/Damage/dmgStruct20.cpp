#include "Game/Damage/dmgStruct20.h"

namespace uking::dmg {

void Struct20::reset() {
    mField_8 = 0;
    mField_C = 0;
    mField_10 = 0;
    mField_14 = -1;
    mField_18 = -1;
}

void Struct20::combineMaybe(Struct20Base* other) {
    Struct20* otherStruct = sead::DynamicCast<Struct20>(other);
    if (!otherStruct) {
        return;
    }

    mField_8 += otherStruct->mField_8;
    mField_C += otherStruct->mField_C;
    mField_10 += otherStruct->mField_10;
    if (mField_18 < otherStruct->mField_18) {
        mField_14 = otherStruct->mField_14;
        mField_18 = otherStruct->mField_18;
    }
}

void Struct20_2::reset() {
    mField_1C = 0;
    mField_30 = false;

    Struct20::reset();
}

void Struct20_2::combineMaybe(Struct20Base* other) {
    Struct20_2* otherStruct = sead::DynamicCast<Struct20_2>(other);
    if (!otherStruct) {
        Struct20::combineMaybe(other);
        return;
    }

    mField_1C |= otherStruct->mField_1C;
    Struct20::combineMaybe(other);
    if (mField_18 == otherStruct->mField_18 && otherStruct->mField_30) {
        mField_30 = true;
        mField_20 = otherStruct->mField_20;
        mField_24 = otherStruct->mField_24;
        mField_28 = otherStruct->mField_28;
        mField_2C = otherStruct->mField_2C;
    }
}

}  // namespace uking::dmg
