#include "Game/AI/Action/actionGanonFallAttack.h"

namespace uking::action {

GanonFallAttack::GanonFallAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonFallAttack::~GanonFallAttack() = default;

bool GanonFallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonFallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonFallAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonFallAttack::loadParams_() {
    getStaticParam(&mIsEmitShockWave_s, "IsEmitShockWave");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonFallAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
