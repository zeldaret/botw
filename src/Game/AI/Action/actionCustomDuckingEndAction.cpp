#include "Game/AI/Action/actionCustomDuckingEndAction.h"

namespace uking::action {

CustomDuckingEndAction::CustomDuckingEndAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CustomDuckingEndAction::~CustomDuckingEndAction() = default;

bool CustomDuckingEndAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CustomDuckingEndAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CustomDuckingEndAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void CustomDuckingEndAction::loadParams_() {}

void CustomDuckingEndAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
