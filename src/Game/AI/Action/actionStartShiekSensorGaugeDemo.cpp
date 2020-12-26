#include "Game/AI/Action/actionStartShiekSensorGaugeDemo.h"

namespace uking::action {

StartShiekSensorGaugeDemo::StartShiekSensorGaugeDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

StartShiekSensorGaugeDemo::~StartShiekSensorGaugeDemo() = default;

bool StartShiekSensorGaugeDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartShiekSensorGaugeDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StartShiekSensorGaugeDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void StartShiekSensorGaugeDemo::loadParams_() {
    getDynamicParam(&mReactionNum_d, "ReactionNum");
}

void StartShiekSensorGaugeDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
