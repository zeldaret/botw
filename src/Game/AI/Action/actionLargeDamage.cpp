#include "Game/AI/Action/actionLargeDamage.h"

namespace uking::action {

LargeDamage::LargeDamage(const InitArg& arg) : ActionEx(arg) {}

LargeDamage::~LargeDamage() = default;

void LargeDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void LargeDamage::leave_() {
    ActionEx::leave_();
}

void LargeDamage::loadParams_() {
    getStaticParam(&mActionTime_s, "ActionTime");
}

void LargeDamage::calc_() {
    ActionEx::calc_();
}

bool LargeDamage::isChangeable() const {
    return ksys::act::ai::Action::isChangeable();
}

}  // namespace uking::action
