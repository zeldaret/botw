#include "Game/AI/Action/actionDisappearNumHeroSeal.h"

namespace uking::action {

DisappearNumHeroSeal::DisappearNumHeroSeal(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumHeroSeal::~DisappearNumHeroSeal() = default;

bool DisappearNumHeroSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumHeroSeal::loadParams_() {}

}  // namespace uking::action
