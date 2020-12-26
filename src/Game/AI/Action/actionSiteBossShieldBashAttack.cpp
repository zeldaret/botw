#include "Game/AI/Action/actionSiteBossShieldBashAttack.h"

namespace uking::action {

SiteBossShieldBashAttack::SiteBossShieldBashAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShieldBashAttack::~SiteBossShieldBashAttack() = default;

bool SiteBossShieldBashAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShieldBashAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossShieldBashAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossShieldBashAttack::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mKeepDist_s, "KeepDist");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossShieldBashAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
