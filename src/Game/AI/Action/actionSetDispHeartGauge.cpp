#include "Game/AI/Action/actionSetDispHeartGauge.h"

namespace uking::action {

SetDispHeartGauge::SetDispHeartGauge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetDispHeartGauge::~SetDispHeartGauge() = default;

bool SetDispHeartGauge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetDispHeartGauge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetDispHeartGauge::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetDispHeartGauge::loadParams_() {
    getDynamicParam(&mIsDisplay_d, "IsDisplay");
    getDynamicParam(&mIsDisplayEx_d, "IsDisplayEx");
    getDynamicParam(&mIsGetDemo_d, "IsGetDemo");
}

void SetDispHeartGauge::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
