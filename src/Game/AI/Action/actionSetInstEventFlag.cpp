#include "Game/AI/Action/actionSetInstEventFlag.h"

namespace uking::action {

SetInstEventFlag::SetInstEventFlag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetInstEventFlag::~SetInstEventFlag() = default;

bool SetInstEventFlag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetInstEventFlag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetInstEventFlag::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetInstEventFlag::loadParams_() {}

void SetInstEventFlag::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
