#include "Game/AI/Action/actionForbidSettingInstEventFlag.h"

namespace uking::action {

ForbidSettingInstEventFlag::ForbidSettingInstEventFlag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForbidSettingInstEventFlag::~ForbidSettingInstEventFlag() = default;

bool ForbidSettingInstEventFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForbidSettingInstEventFlag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForbidSettingInstEventFlag::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForbidSettingInstEventFlag::loadParams_() {}

void ForbidSettingInstEventFlag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
