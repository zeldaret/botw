#include "Game/AI/Action/actionChuchuPreAttackBase.h"

namespace uking::action {

ChuchuPreAttackBase::ChuchuPreAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChuchuPreAttackBase::~ChuchuPreAttackBase() = default;

bool ChuchuPreAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChuchuPreAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChuchuPreAttackBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChuchuPreAttackBase::loadParams_() {
    getStaticParam(&mJumpNum_s, "JumpNum");
    getStaticParam(&mMoveBoneRotRatio_s, "MoveBoneRotRatio");
    getStaticParam(&mMoveBoneRotSpeedMin_s, "MoveBoneRotSpeedMin");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ChuchuPreAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
