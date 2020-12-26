#include "Game/AI/Action/actionSetDispStaminaGauge.h"

namespace uking::action {

SetDispStaminaGauge::SetDispStaminaGauge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetDispStaminaGauge::~SetDispStaminaGauge() = default;

bool SetDispStaminaGauge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetDispStaminaGauge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetDispStaminaGauge::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetDispStaminaGauge::loadParams_() {
    getDynamicParam(&mIsDisplay_d, "IsDisplay");
    getDynamicParam(&mIsDisplayEx_d, "IsDisplayEx");
}

void SetDispStaminaGauge::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
