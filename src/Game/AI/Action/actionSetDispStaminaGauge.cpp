#include "Game/AI/Action/actionSetDispStaminaGauge.h"

namespace uking::action {

SetDispStaminaGauge::SetDispStaminaGauge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetDispStaminaGauge::~SetDispStaminaGauge() = default;

bool SetDispStaminaGauge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetDispStaminaGauge::loadParams_() {
    getDynamicParam(&mIsDisplay_d, "IsDisplay");
    getDynamicParam(&mIsDisplayEx_d, "IsDisplayEx");
}

}  // namespace uking::action
