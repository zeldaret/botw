#include "Game/Actor/AI/aiGoronCannon.h"

namespace uking::ai {

GoronCannon::GoronCannon(const InitArg& arg) : BigCannon(arg) {}

GoronCannon::~GoronCannon() = default;

bool GoronCannon::init_(sead::Heap* heap) {
    return BigCannon::init_(heap);
}

void GoronCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    BigCannon::enter_(params);
}

void GoronCannon::leave_() {
    BigCannon::leave_();
}

void GoronCannon::loadParams_() {
    BigCannon::loadParams_();
}

}  // namespace uking::ai
