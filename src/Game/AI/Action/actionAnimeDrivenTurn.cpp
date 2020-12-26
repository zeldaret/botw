#include "Game/AI/Action/actionAnimeDrivenTurn.h"

namespace uking::action {

AnimeDrivenTurn::AnimeDrivenTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimeDrivenTurn::~AnimeDrivenTurn() = default;

bool AnimeDrivenTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimeDrivenTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimeDrivenTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimeDrivenTurn::loadParams_() {
    getStaticParam(&mAllowChangeableFrame_s, "AllowChangeableFrame");
    getStaticParam(&mAnimPlayRate_s, "AnimPlayRate");
    getStaticParam(&mFinishAngleRange_s, "FinishAngleRange");
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mIsAllowAnimeDrivenNoChangeAS_s, "IsAllowAnimeDrivenNoChangeAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimeDrivenTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
