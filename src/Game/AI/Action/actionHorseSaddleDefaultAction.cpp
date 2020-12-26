#include "Game/AI/Action/actionHorseSaddleDefaultAction.h"

namespace uking::action {

HorseSaddleDefaultAction::HorseSaddleDefaultAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

HorseSaddleDefaultAction::~HorseSaddleDefaultAction() = default;

bool HorseSaddleDefaultAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseSaddleDefaultAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseSaddleDefaultAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseSaddleDefaultAction::loadParams_() {}

void HorseSaddleDefaultAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
