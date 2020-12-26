#include "Game/AI/Action/actionDownloadShiekSensor.h"

namespace uking::action {

DownloadShiekSensor::DownloadShiekSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DownloadShiekSensor::~DownloadShiekSensor() = default;

bool DownloadShiekSensor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DownloadShiekSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DownloadShiekSensor::leave_() {
    ksys::act::ai::Action::leave_();
}

void DownloadShiekSensor::loadParams_() {}

void DownloadShiekSensor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
