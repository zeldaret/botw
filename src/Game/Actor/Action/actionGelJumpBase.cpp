#include "Game/Actor/Action/actionGelJumpBase.h"

namespace uking::action {

GelJumpBase::GelJumpBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GelJumpBase::~GelJumpBase() = default;

bool GelJumpBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GelJumpBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GelJumpBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void GelJumpBase::loadParams_() {
    getStaticParam(&mJumpNum_s, "JumpNum");
    getStaticParam(&mMoveBoneRotRatio_s, "MoveBoneRotRatio");
    getStaticParam(&mMoveBoneRotSpeedMin_s, "MoveBoneRotSpeedMin");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GelJumpBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
