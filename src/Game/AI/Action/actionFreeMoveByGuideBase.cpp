#include "Game/AI/Action/actionFreeMoveByGuideBase.h"

namespace uking::action {

FreeMoveByGuideBase::FreeMoveByGuideBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FreeMoveByGuideBase::~FreeMoveByGuideBase() = default;

bool FreeMoveByGuideBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreeMoveByGuideBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FreeMoveByGuideBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void FreeMoveByGuideBase::loadParams_() {
    getStaticParam(&mRotateAngleMax_s, "RotateAngleMax");
    getStaticParam(&mMaxAngleAcc_s, "MaxAngleAcc");
    getStaticParam(&mAngleAccRatio_s, "AngleAccRatio");
    getStaticParam(&mKeepPlacementRotation_s, "KeepPlacementRotation");
    getStaticParam(&mIsTraceRailPointRotation_s, "IsTraceRailPointRotation");
    getStaticParam(&mKeepRotationBaseBoneName_s, "KeepRotationBaseBoneName");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetFrontDir_d, "TargetFrontDir");
}

void FreeMoveByGuideBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
