#include "Game/AI/Action/actionGoronHeroDescendentAppear.h"

namespace uking::action {

GoronHeroDescendentAppear::GoronHeroDescendentAppear(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GoronHeroDescendentAppear::~GoronHeroDescendentAppear() = default;

bool GoronHeroDescendentAppear::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GoronHeroDescendentAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GoronHeroDescendentAppear::leave_() {
    ksys::act::ai::Action::leave_();
}

void GoronHeroDescendentAppear::loadParams_() {}

void GoronHeroDescendentAppear::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
