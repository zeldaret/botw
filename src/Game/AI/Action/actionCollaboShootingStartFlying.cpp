#include "Game/AI/Action/actionCollaboShootingStartFlying.h"

namespace uking::action {

CollaboShootingStartFlying::CollaboShootingStartFlying(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStartFlying::~CollaboShootingStartFlying() = default;

bool CollaboShootingStartFlying::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaboShootingStartFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CollaboShootingStartFlying::leave_() {
    ksys::act::ai::Action::leave_();
}

void CollaboShootingStartFlying::loadParams_() {
    getStaticParam(&mInitialVelocityMax_s, "InitialVelocityMax");
    getStaticParam(&mInitialVelocityMin_s, "InitialVelocityMin");
    getStaticParam(&mLookSuccessRate_s, "LookSuccessRate");
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    // FIXME: CALL _ZN4sead14SafeStringBaseIcEaSERKS1_ @ 0x7100b0caa0
    // FIXME: CALL _ZNK4sead14SafeStringBaseIcE22assureTerminationImpl_Ev @ 0x89
    // FIXME: CALL _ZN4sead9HashCRC3214calcStringHashEPKc @ 0x7100b2170c
}

void CollaboShootingStartFlying::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
