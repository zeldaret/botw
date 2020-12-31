#include "Game/AI/AI/aiGoronCannon.h"

namespace uking::ai {

GoronCannon::GoronCannon(const InitArg& arg) : GoronCannonBase(arg) {}

GoronCannon::~GoronCannon() = default;

bool GoronCannon::init_(sead::Heap* heap) {
    return GoronCannonBase::init_(heap);
}

void GoronCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    GoronCannonBase::enter_(params);
}

void GoronCannon::leave_() {
    GoronCannonBase::leave_();
}

void GoronCannon::loadParams_() {
    GoronCannonBase::loadParams_();
}

}  // namespace uking::ai
