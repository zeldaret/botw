#include "Game/AI/Action/actionBikeWarpEffectValueSetter.h"

namespace uking::action {

BikeWarpEffectValueSetter::BikeWarpEffectValueSetter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BikeWarpEffectValueSetter::~BikeWarpEffectValueSetter() = default;

bool BikeWarpEffectValueSetter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BikeWarpEffectValueSetter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BikeWarpEffectValueSetter::leave_() {
    ksys::act::ai::Action::leave_();
}

void BikeWarpEffectValueSetter::loadParams_() {
    getDynamicParam(&mChangeType_d, "ChangeType");
    getDynamicParam(&mSetFrame_d, "SetFrame");
}

void BikeWarpEffectValueSetter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
