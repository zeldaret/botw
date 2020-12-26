#include "Game/AI/Action/actionHorseSwim.h"

namespace uking::action {

HorseSwim::HorseSwim(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseSwim::~HorseSwim() = default;

bool HorseSwim::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseSwim::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseSwim::loadParams_() {}

void HorseSwim::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
