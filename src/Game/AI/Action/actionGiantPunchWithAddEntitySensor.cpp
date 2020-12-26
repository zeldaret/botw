#include "Game/AI/Action/actionGiantPunchWithAddEntitySensor.h"

namespace uking::action {

GiantPunchWithAddEntitySensor::GiantPunchWithAddEntitySensor(const InitArg& arg)
    : GiantPunchAttack(arg) {}

GiantPunchWithAddEntitySensor::~GiantPunchWithAddEntitySensor() = default;

bool GiantPunchWithAddEntitySensor::init_(sead::Heap* heap) {
    return GiantPunchAttack::init_(heap);
}

void GiantPunchWithAddEntitySensor::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantPunchAttack::enter_(params);
}

void GiantPunchWithAddEntitySensor::leave_() {
    GiantPunchAttack::leave_();
}

void GiantPunchWithAddEntitySensor::loadParams_() {
    GiantPunchAttack::loadParams_();
}

void GiantPunchWithAddEntitySensor::calc_() {
    GiantPunchAttack::calc_();
}

}  // namespace uking::action
