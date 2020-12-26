#include "Game/AI/Action/actionEnemyRigidBodyFreeFallDie.h"

namespace uking::action {

EnemyRigidBodyFreeFallDie::EnemyRigidBodyFreeFallDie(const InitArg& arg)
    : EnemyRigidBodyDieBase(arg) {}

EnemyRigidBodyFreeFallDie::~EnemyRigidBodyFreeFallDie() = default;

bool EnemyRigidBodyFreeFallDie::init_(sead::Heap* heap) {
    return EnemyRigidBodyDieBase::init_(heap);
}

void EnemyRigidBodyFreeFallDie::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRigidBodyDieBase::enter_(params);
}

void EnemyRigidBodyFreeFallDie::leave_() {
    EnemyRigidBodyDieBase::leave_();
}

void EnemyRigidBodyFreeFallDie::loadParams_() {
    EnemyRigidBodyDieBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void EnemyRigidBodyFreeFallDie::calc_() {
    EnemyRigidBodyDieBase::calc_();
}

}  // namespace uking::action
