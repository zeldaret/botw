#include "Game/AI/Action/actionEnemyRigidBodySpinDie.h"

namespace uking::action {

EnemyRigidBodySpinDie::EnemyRigidBodySpinDie(const InitArg& arg) : EnemyRigidBodyDieBase(arg) {}

EnemyRigidBodySpinDie::~EnemyRigidBodySpinDie() = default;

bool EnemyRigidBodySpinDie::init_(sead::Heap* heap) {
    return EnemyRigidBodyDieBase::init_(heap);
}

void EnemyRigidBodySpinDie::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRigidBodyDieBase::enter_(params);
}

void EnemyRigidBodySpinDie::leave_() {
    EnemyRigidBodyDieBase::leave_();
}

void EnemyRigidBodySpinDie::loadParams_() {
    EnemyRigidBodyDieBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mIsFinishedByBgHit_s, "IsFinishedByBgHit");
    getStaticParam(&mASName_s, "ASName");
}

void EnemyRigidBodySpinDie::calc_() {
    EnemyRigidBodyDieBase::calc_();
}

}  // namespace uking::action
