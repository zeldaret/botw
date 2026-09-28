#include "Game/Actor/Damage/actStruct20.h"

namespace uking::act {

void Struct20_2::reset() {
    mField_1C = 0;
    mField_30 = false;

    Struct20::reset();
}

void Struct20_2::combineMaybe(ksys::act::Struct20Base* other) {
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

}  // namespace uking::act
