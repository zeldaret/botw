#include "Game/AI/Action/actionRemoveSensor.h"

namespace uking::action {

RemoveSensor::RemoveSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemoveSensor::~RemoveSensor() = default;

bool RemoveSensor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemoveSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemoveSensor::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemoveSensor::loadParams_() {
    getStaticParam(&mAddSensorOnLeave_s, "AddSensorOnLeave");
}

void RemoveSensor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
