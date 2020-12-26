#include "Game/AI/Action/actionForkGanonBeastWeakPointCheck.h"

namespace uking::action {

ForkGanonBeastWeakPointCheck::ForkGanonBeastWeakPointCheck(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastWeakPointCheck::~ForkGanonBeastWeakPointCheck() = default;

bool ForkGanonBeastWeakPointCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastWeakPointCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonBeastWeakPointCheck::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastWeakPointCheck::loadParams_() {
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mLastWeakCounter_s, "LastWeakCounter");
    getStaticParam(&mLastWeakSlowEndSafeTime_s, "LastWeakSlowEndSafeTime");
    getAITreeVariable(&mLastDamageWeakPointIdx_a, "LastDamageWeakPointIdx");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mGanonBeastWeakPointXLinkHandle_a, "GanonBeastWeakPointXLinkHandle");
    getAITreeVariable(&mWeakPointCounter_a, "WeakPointCounter");
}

void ForkGanonBeastWeakPointCheck::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
