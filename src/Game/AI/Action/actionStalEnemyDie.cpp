#include "Game/AI/Action/actionStalEnemyDie.h"

namespace uking::action {

StalEnemyDie::StalEnemyDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StalEnemyDie::~StalEnemyDie() = default;

bool StalEnemyDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StalEnemyDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StalEnemyDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void StalEnemyDie::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mForceDropWeapon_s, "ForceDropWeapon");
    getStaticParam(&mPreDieASName_s, "PreDieASName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollName_s, "PosBaseRagdollName");
    getStaticParam(&mEnableConstraintName_s, "EnableConstraintName");
}

void StalEnemyDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
