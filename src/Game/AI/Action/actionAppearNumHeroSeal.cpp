#include "Game/AI/Action/actionAppearNumHeroSeal.h"

namespace uking::action {

AppearNumHeroSeal::AppearNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumHeroSeal::~AppearNumHeroSeal() = default;

bool AppearNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumHeroSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearNumHeroSeal::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearNumHeroSeal::loadParams_() {
    getDynamicParam(&mRelicPattern_d, "RelicPattern");
}

void AppearNumHeroSeal::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
