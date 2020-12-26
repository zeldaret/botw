#include "Game/AI/Action/actionIncreaseNumHeroSeal.h"

namespace uking::action {

IncreaseNumHeroSeal::IncreaseNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IncreaseNumHeroSeal::~IncreaseNumHeroSeal() = default;

bool IncreaseNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreaseNumHeroSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IncreaseNumHeroSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreaseNumHeroSeal::loadParams_() {
    getDynamicParam(&mRelicPattern_d, "RelicPattern");
    getDynamicParam(&mValue_d, "Value");
}

void IncreaseNumHeroSeal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
