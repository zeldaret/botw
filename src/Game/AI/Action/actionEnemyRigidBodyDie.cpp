#include "Game/AI/Action/actionEnemyRigidBodyDie.h"

namespace uking::action {

EnemyRigidBodyDie::EnemyRigidBodyDie(const InitArg& arg) : EnemyRigidBodyDieBase(arg) {}

EnemyRigidBodyDie::~EnemyRigidBodyDie() = default;

bool EnemyRigidBodyDie::init_(sead::Heap* heap) {
    return EnemyRigidBodyDieBase::init_(heap);
}

void EnemyRigidBodyDie::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRigidBodyDieBase::enter_(params);
}

void EnemyRigidBodyDie::leave_() {
    EnemyRigidBodyDieBase::leave_();
}

void EnemyRigidBodyDie::loadParams_() {
    EnemyRigidBodyDieBase::loadParams_();
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mASName_s, "ASName");
}

void EnemyRigidBodyDie::calc_() {
    EnemyRigidBodyDieBase::calc_();
}

}  // namespace uking::action
