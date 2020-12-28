#include "Game/AI/Action/actionAttackPartBind.h"

namespace uking::action {

AttackPartBind::AttackPartBind(const InitArg& arg) : Attack(arg) {}

AttackPartBind::~AttackPartBind() = default;

void AttackPartBind::enter_(ksys::act::ai::InlineParamPack* params) {
    Attack::enter_(params);
}

void AttackPartBind::leave_() {
    Attack::leave_();
}

void AttackPartBind::loadParams_() {
    Attack::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
}

void AttackPartBind::calc_() {
    Attack::calc_();
}

}  // namespace uking::action
