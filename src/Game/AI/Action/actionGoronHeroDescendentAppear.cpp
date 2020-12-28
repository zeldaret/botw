#include "Game/AI/Action/actionGoronHeroDescendentAppear.h"

namespace uking::action {

GoronHeroDescendentAppear::GoronHeroDescendentAppear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GoronHeroDescendentAppear::~GoronHeroDescendentAppear() = default;

bool GoronHeroDescendentAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GoronHeroDescendentAppear::loadParams_() {}

}  // namespace uking::action
