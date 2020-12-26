#include "Game/AI/Action/actionGanonBeastDamageASPlay.h"

namespace uking::action {

GanonBeastDamageASPlay::GanonBeastDamageASPlay(const InitArg& arg) : ForkASPlayBase(arg) {}

GanonBeastDamageASPlay::~GanonBeastDamageASPlay() = default;

bool GanonBeastDamageASPlay::init_(sead::Heap* heap) {
    return ForkASPlayBase::init_(heap);
}

void GanonBeastDamageASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASPlayBase::enter_(params);
}

void GanonBeastDamageASPlay::leave_() {
    ForkASPlayBase::leave_();
}

void GanonBeastDamageASPlay::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mIsStateChange_s, "IsStateChange");
    getAITreeVariable(&mLastDamageWeakPointIdx_a, "LastDamageWeakPointIdx");
}

void GanonBeastDamageASPlay::calc_() {
    ForkASPlayBase::calc_();
}

}  // namespace uking::action
