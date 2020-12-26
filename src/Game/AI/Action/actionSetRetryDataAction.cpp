#include "Game/AI/Action/actionSetRetryDataAction.h"

namespace uking::action {

SetRetryDataAction::SetRetryDataAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetRetryDataAction::~SetRetryDataAction() = default;

bool SetRetryDataAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetRetryDataAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetRetryDataAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetRetryDataAction::loadParams_() {}

void SetRetryDataAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
