#include "Game/AI/Action/actionDisappearNumHeroSeal.h"

namespace uking::action {

DisappearNumHeroSeal::DisappearNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumHeroSeal::~DisappearNumHeroSeal() = default;

bool DisappearNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumHeroSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DisappearNumHeroSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void DisappearNumHeroSeal::loadParams_() {}

void DisappearNumHeroSeal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
