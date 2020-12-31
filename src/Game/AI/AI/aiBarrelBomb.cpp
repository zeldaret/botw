#include "Game/AI/AI/aiBarrelBomb.h"

namespace uking::ai {

BarrelBomb::BarrelBomb(const InitArg& arg) : SimpleLiftable(arg) {}

bool BarrelBomb::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void BarrelBomb::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
}

void BarrelBomb::leave_() {
    SimpleLiftable::leave_();
}

void BarrelBomb::loadParams_() {
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
}

}  // namespace uking::ai
