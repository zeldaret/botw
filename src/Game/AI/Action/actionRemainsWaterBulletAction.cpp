#include "Game/AI/Action/actionRemainsWaterBulletAction.h"

namespace uking::action {

RemainsWaterBulletAction::RemainsWaterBulletAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainsWaterBulletAction::~RemainsWaterBulletAction() = default;

bool RemainsWaterBulletAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainsWaterBulletAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainsWaterBulletAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainsWaterBulletAction::loadParams_() {
    getStaticParam(&mSignASFrame_s, "SignASFrame");
    getStaticParam(&mMaxRotSpd_s, "MaxRotSpd");
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mIgnroeWater_s, "IgnroeWater");
    getStaticParam(&mIgnoreGravity_s, "IgnoreGravity");
    getStaticParam(&mUseParentRevDirRot_s, "UseParentRevDirRot");
    getStaticParam(&mSignASName_s, "SignASName");
}

void RemainsWaterBulletAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
