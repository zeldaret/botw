#include "Game/AI/Action/actionSiteBossLswordFirstCreateFBall.h"

namespace uking::action {

SiteBossLswordFirstCreateFBall::SiteBossLswordFirstCreateFBall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordFirstCreateFBall::~SiteBossLswordFirstCreateFBall() = default;

bool SiteBossLswordFirstCreateFBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordFirstCreateFBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordFirstCreateFBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordFirstCreateFBall::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mCreateNum_s, "CreateNum");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mFireBallScale_s, "FireBallScale");
    getStaticParam(&mThrowActorName_s, "ThrowActorName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mBindPosOffset_s, "BindPosOffset");
}

void SiteBossLswordFirstCreateFBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
