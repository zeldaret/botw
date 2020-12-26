#include "Game/AI/Action/actionUKingEmitEffectLoopAction.h"

namespace uking::action {

UKingEmitEffectLoopAction::UKingEmitEffectLoopAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

UKingEmitEffectLoopAction::~UKingEmitEffectLoopAction() = default;

bool UKingEmitEffectLoopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void UKingEmitEffectLoopAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void UKingEmitEffectLoopAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void UKingEmitEffectLoopAction::loadParams_() {
    getDynamicParam(&mScale_d, "Scale");
    getDynamicParam(&mX_d, "X");
    getDynamicParam(&mY_d, "Y");
    getDynamicParam(&mZ_d, "Z");
    getDynamicParam(&mRX_d, "RX");
    getDynamicParam(&mRY_d, "RY");
    getDynamicParam(&mRZ_d, "RZ");
    getDynamicParam(&mR_d, "R");
    getDynamicParam(&mG_d, "G");
    getDynamicParam(&mB_d, "B");
    getDynamicParam(&mA_d, "A");
    getDynamicParam(&mNoFade_d, "NoFade");
    getDynamicParam(&mOverWrite_d, "OverWrite");
    getDynamicParam(&mCutChangeReset_d, "CutChangeReset");
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mOption_d, "Option");
}

void UKingEmitEffectLoopAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
