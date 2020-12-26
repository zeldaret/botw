#include "Game/AI/Action/actionControlBombEffect.h"

namespace uking::action {

ControlBombEffect::ControlBombEffect(const InitArg& arg) : AreaTagAction(arg) {}

ControlBombEffect::~ControlBombEffect() = default;

bool ControlBombEffect::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void ControlBombEffect::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ControlBombEffect::leave_() {
    AreaTagAction::leave_();
}

void ControlBombEffect::loadParams_() {}

void ControlBombEffect::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
