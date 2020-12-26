#include "Game/AI/Action/actionWarpEffectValueSetter.h"

namespace uking::action {

WarpEffectValueSetter::WarpEffectValueSetter(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpEffectValueSetter::~WarpEffectValueSetter() = default;

bool WarpEffectValueSetter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpEffectValueSetter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpEffectValueSetter::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpEffectValueSetter::loadParams_() {
    getDynamicParam(&mChangeType_d, "ChangeType");
    getDynamicParam(&mSetFrame_d, "SetFrame");
}

void WarpEffectValueSetter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
