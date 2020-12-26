#include "Game/AI/Action/actionPlayerWarpEffectValueSetter.h"

namespace uking::action {

PlayerWarpEffectValueSetter::PlayerWarpEffectValueSetter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PlayerWarpEffectValueSetter::~PlayerWarpEffectValueSetter() = default;

bool PlayerWarpEffectValueSetter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerWarpEffectValueSetter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerWarpEffectValueSetter::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerWarpEffectValueSetter::loadParams_() {
    getDynamicParam(&mChangeType_d, "ChangeType");
    getDynamicParam(&mSetFrame_d, "SetFrame");
}

void PlayerWarpEffectValueSetter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
