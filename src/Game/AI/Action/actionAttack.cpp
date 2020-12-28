#include "Game/AI/Action/actionAttack.h"

namespace uking::action {

Attack::Attack(const InitArg& arg) : AttackBase(arg) {}

Attack::~Attack() = default;

void Attack::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackBase::enter_(params);
}

void Attack::leave_() {
    AttackBase::leave_();
}

void Attack::loadParams_() {
    AttackBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void Attack::calc_() {
    AttackBase::calc_();
}

}  // namespace uking::action
