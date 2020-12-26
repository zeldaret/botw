#include "Game/AI/Action/actionForkASHoldLegTurn.h"

namespace uking::action {

ForkASHoldLegTurn::ForkASHoldLegTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASHoldLegTurn::~ForkASHoldLegTurn() = default;

bool ForkASHoldLegTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASHoldLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASHoldLegTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASHoldLegTurn::loadParams_() {
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mStopSpeedRatio_s, "StopSpeedRatio");
    getStaticParam(&mStopRotSpeedRatio_s, "StopRotSpeedRatio");
    getStaticParam(&mTargetPosNoUpdateArea_s, "TargetPosNoUpdateArea");
    getStaticParam(&mIsFixBoneWithGround_s, "IsFixBoneWithGround");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkASHoldLegTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
