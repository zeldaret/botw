#include "Game/AI/Action/actionEmitEffectLoopAction.h"

namespace uking::action {

EmitEffectLoopAction::EmitEffectLoopAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitEffectLoopAction::~EmitEffectLoopAction() = default;

bool EmitEffectLoopAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EmitEffectLoopAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EmitEffectLoopAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EmitEffectLoopAction::loadParams_() {
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
    getDynamicParam(&mOverWrite_d, "OverWrite");
    getDynamicParam(&mNoFade_d, "NoFade");
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
    getDynamicParam(&mELinkKey_d, "ELinkKey");
    getDynamicParam(&mOption_d, "Option");
    getDynamicParam(&mCutChangeReset_d, "CutChangeReset");
}

void EmitEffectLoopAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
