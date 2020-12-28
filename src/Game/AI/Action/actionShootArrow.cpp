#include "Game/AI/Action/actionShootArrow.h"

namespace uking::action {

ShootArrow::ShootArrow(const InitArg& arg) : ActionEx(arg) {}

ShootArrow::~ShootArrow() = default;

void ShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ShootArrow::loadParams_() {}

void ShootArrow::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
