#include "Game/AI/Action/actionReloadArrow.h"

namespace uking::action {

ReloadArrow::ReloadArrow(const InitArg& arg) : ActionEx(arg) {}

ReloadArrow::~ReloadArrow() = default;

void ReloadArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ReloadArrow::leave_() {
    ActionEx::leave_();
}

void ReloadArrow::loadParams_() {}

void ReloadArrow::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
