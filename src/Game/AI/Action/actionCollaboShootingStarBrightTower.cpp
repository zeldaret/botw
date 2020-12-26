#include "Game/AI/Action/actionCollaboShootingStarBrightTower.h"

namespace uking::action {

CollaboShootingStarBrightTower::CollaboShootingStarBrightTower(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStarBrightTower::~CollaboShootingStarBrightTower() = default;

bool CollaboShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaboShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CollaboShootingStarBrightTower::leave_() {
    ksys::act::ai::Action::leave_();
}

void CollaboShootingStarBrightTower::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    // FIXME: CALL _ZNK4sead14SafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL _ZN4sead9HashCRC3214calcStringHashEPKc @ 0x7100b2170c
}

void CollaboShootingStarBrightTower::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
