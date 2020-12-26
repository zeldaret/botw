#include "Game/AI/Action/actionHorseVanish.h"

namespace uking::action {

HorseVanish::HorseVanish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseVanish::~HorseVanish() = default;

bool HorseVanish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseVanish::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseVanish::loadParams_() {}

void HorseVanish::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
