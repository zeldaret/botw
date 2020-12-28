#include "Game/AI/Action/actionAppearNumHeroSeal.h"

namespace uking::action {

AppearNumHeroSeal::AppearNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumHeroSeal::~AppearNumHeroSeal() = default;

bool AppearNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumHeroSeal::loadParams_() {
    getDynamicParam(&mRelicPattern_d, "RelicPattern");
}

}  // namespace uking::action
