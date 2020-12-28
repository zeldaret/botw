#include "Game/AI/Action/actionHorseReinsDefaultAction.h"

namespace uking::action {

HorseReinsDefaultAction::HorseReinsDefaultAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseReinsDefaultAction::~HorseReinsDefaultAction() = default;

void HorseReinsDefaultAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseReinsDefaultAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseReinsDefaultAction::loadParams_() {}

void HorseReinsDefaultAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
