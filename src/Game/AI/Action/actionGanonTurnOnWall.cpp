#include "Game/AI/Action/actionGanonTurnOnWall.h"

namespace uking::action {

GanonTurnOnWall::GanonTurnOnWall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonTurnOnWall::~GanonTurnOnWall() = default;

bool GanonTurnOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonTurnOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonTurnOnWall::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonTurnOnWall::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonTurnOnWall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
