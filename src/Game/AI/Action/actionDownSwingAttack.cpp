#include "Game/AI/Action/actionDownSwingAttack.h"

namespace uking::action {

DownSwingAttack::DownSwingAttack(const InitArg& arg) : ActionEx(arg) {}

DownSwingAttack::~DownSwingAttack() = default;

void DownSwingAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void DownSwingAttack::leave_() {
    ActionEx::leave_();
}

void DownSwingAttack::loadParams_() {}

void DownSwingAttack::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
