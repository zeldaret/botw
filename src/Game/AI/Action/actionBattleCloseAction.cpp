#include "Game/AI/Action/actionBattleCloseAction.h"

namespace uking::action {

BattleCloseAction::BattleCloseAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleCloseAction::~BattleCloseAction() = default;

bool BattleCloseAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleCloseAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BattleCloseAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void BattleCloseAction::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BattleCloseAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
