#include "Game/AI/Action/actionSetDispHeartGauge.h"

namespace uking::action {

SetDispHeartGauge::SetDispHeartGauge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetDispHeartGauge::~SetDispHeartGauge() = default;

bool SetDispHeartGauge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetDispHeartGauge::loadParams_() {
    getDynamicParam(&mIsDisplay_d, "IsDisplay");
    getDynamicParam(&mIsDisplayEx_d, "IsDisplayEx");
    getDynamicParam(&mIsGetDemo_d, "IsGetDemo");
}

}  // namespace uking::action
