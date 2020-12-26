#include "Game/AI/Action/actionForkTurn.h"

namespace uking::action {

ForkTurn::ForkTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkTurn::~ForkTurn() = default;

bool ForkTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkTurn::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRotAccMaxSpeedRatio_s, "RotAccMaxSpeedRatio");
    getStaticParam(&mIsUpdateTarget_s, "IsUpdateTarget");
    getStaticParam(&mIsFollowGround_s, "IsFollowGround");
    getStaticParam(&mIsRotEndFinish_s, "IsRotEndFinish");
    getStaticParam(&mIsFinishForceStopRot_s, "IsFinishForceStopRot");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsUpFollow_s, "IsUpFollow");
}

void ForkTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
