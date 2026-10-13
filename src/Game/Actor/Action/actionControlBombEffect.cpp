#include "Game/Actor/Action/actionControlBombEffect.h"

namespace uking::action {

ControlBombEffect::ControlBombEffect(const InitArg& arg) : AreaActionBase(arg) {}

ControlBombEffect::~ControlBombEffect() = default;

bool ControlBombEffect::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void ControlBombEffect::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void ControlBombEffect::leave_() {
    AreaActionBase::leave_();
}

void ControlBombEffect::loadParams_() {}

void ControlBombEffect::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
