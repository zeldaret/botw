#include "Game/AI/Action/actionHorseReinsDefaultAction.h"

namespace uking::action {

HorseReinsDefaultAction::HorseReinsDefaultAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseReinsDefaultAction::~HorseReinsDefaultAction() = default;

bool HorseReinsDefaultAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

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
