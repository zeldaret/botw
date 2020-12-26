#include "Game/AI/Action/actionHorseFallAction.h"

namespace uking::action {

HorseFallAction::HorseFallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseFallAction::~HorseFallAction() = default;

bool HorseFallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseFallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseFallAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseFallAction::loadParams_() {}

void HorseFallAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
