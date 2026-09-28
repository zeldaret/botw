#include "Game/Actor/Action/actionAttack.h"

namespace uking::action {

Attack::Attack(const InitArg& arg) : StoppingAttackBase(arg) {}

Attack::~Attack() = default;

void Attack::enter_(ksys::act::ai::InlineParamPack* params) {
    StoppingAttackBase::enter_(params);
}

void Attack::leave_() {
    StoppingAttackBase::leave_();
}

void Attack::loadParams_() {
    StoppingAttackBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void Attack::calc_() {
    StoppingAttackBase::calc_();
}

}  // namespace uking::action
