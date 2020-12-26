#include "Game/AI/Action/actionHorseRodeo.h"

namespace uking::action {

HorseRodeo::HorseRodeo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRodeo::~HorseRodeo() = default;

bool HorseRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseRodeo::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseRodeo::loadParams_() {}

void HorseRodeo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
