#include "Game/AI/Action/actionBattleCloseLevelFlyMoveBase.h"

namespace uking::action {

BattleCloseLevelFlyMoveBase::BattleCloseLevelFlyMoveBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BattleCloseLevelFlyMoveBase::~BattleCloseLevelFlyMoveBase() = default;

bool BattleCloseLevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleCloseLevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleCloseLevelFlyMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void BattleCloseLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mXZSpeed_s, "XZSpeed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mVerticalFinLength_s, "VerticalFinLength");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mDownSpeed_s, "DownSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    // FIXME: CALL sub_71006F3DF8 @ 0x71006f3df8
}

void BattleCloseLevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
