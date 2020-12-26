#include "Game/AI/Action/actionForkStalEnemyForceDamage.h"

namespace uking::action {

ForkStalEnemyForceDamage::ForkStalEnemyForceDamage(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkStalEnemyForceDamage::~ForkStalEnemyForceDamage() = default;

bool ForkStalEnemyForceDamage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkStalEnemyForceDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkStalEnemyForceDamage::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkStalEnemyForceDamage::loadParams_() {
    getStaticParam(&mDamage_s, "Damage");
    getStaticParam(&mASTrigType_s, "ASTrigType");
    getStaticParam(&mDamageType_s, "DamageType");
    getStaticParam(&mDamageAttr_s, "DamageAttr");
    getStaticParam(&mLifeRate_s, "LifeRate");
}

void ForkStalEnemyForceDamage::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
