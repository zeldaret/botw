#include "Game/AI/Action/actionEnemyRigidBodyDieBase.h"

namespace uking::action {

EnemyRigidBodyDieBase::EnemyRigidBodyDieBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EnemyRigidBodyDieBase::~EnemyRigidBodyDieBase() = default;

bool EnemyRigidBodyDieBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EnemyRigidBodyDieBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EnemyRigidBodyDieBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void EnemyRigidBodyDieBase::loadParams_() {
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
}

void EnemyRigidBodyDieBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
