#include "Game/AI/Action/actionDragonMoveTo.h"

namespace uking::action {

DragonMoveTo::DragonMoveTo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonMoveTo::~DragonMoveTo() = default;

bool DragonMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DragonMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DragonMoveTo::leave_() {
    ksys::act::ai::Action::leave_();
}

void DragonMoveTo::loadParams_() {
    getStaticParam(&mRollMax_s, "RollMax");
    getStaticParam(&mRollSpeed_s, "RollSpeed");
    getStaticParam(&mRollMaxSpeed_s, "RollMaxSpeed");
    getStaticParam(&mRollAmount_s, "RollAmount");
    getStaticParam(&mRestoreUp_s, "RestoreUp");
    getStaticParam(&mBackAdjustAngle_s, "BackAdjustAngle");
    getStaticParam(&mBackAdjustRestoreUp_s, "BackAdjustRestoreUp");
    getStaticParam(&mFixAngle_s, "FixAngle");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mFrontDir_d, "FrontDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DragonMoveTo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
