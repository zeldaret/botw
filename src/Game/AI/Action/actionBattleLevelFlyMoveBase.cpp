#include "Game/AI/Action/actionBattleLevelFlyMoveBase.h"

namespace uking::action {

BattleLevelFlyMoveBase::BattleLevelFlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleLevelFlyMoveBase::~BattleLevelFlyMoveBase() = default;

bool BattleLevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleLevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleLevelFlyMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void BattleLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mCheckStopSpeed_s, "CheckStopSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BattleLevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
