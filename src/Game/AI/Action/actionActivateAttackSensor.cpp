#include "Game/AI/Action/actionActivateAttackSensor.h"

namespace uking::action {

ActivateAttackSensor::ActivateAttackSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActivateAttackSensor::~ActivateAttackSensor() = default;

bool ActivateAttackSensor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ActivateAttackSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ActivateAttackSensor::leave_() {
    ksys::act::ai::Action::leave_();
}

void ActivateAttackSensor::loadParams_() {
    getStaticParam(&mAtDamage_s, "AtDamage");
    getStaticParam(&mAtPower_s, "AtPower");
    getStaticParam(&mAtPowerReduce_s, "AtPowerReduce");
    getStaticParam(&mAtImpact_s, "AtImpact");
    getStaticParam(&mAtShieldBreakPower_s, "AtShieldBreakPower");
    getStaticParam(&mAtType_s, "AtType");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mAtDirType_s, "AtDirType");
    getStaticParam(&mFramesActive_s, "FramesActive");
    getStaticParam(&mIsSuccessFinishCounterEnd_s, "IsSuccessFinishCounterEnd");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mUseMapUnitParamForDamage_s, "UseMapUnitParamForDamage");
    getStaticParam(&mAtkSensorName_s, "AtkSensorName");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

void ActivateAttackSensor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
