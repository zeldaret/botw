#include "Game/Actor/Action/actionEquipHornUseBase.h"

namespace uking::action {

EquipHornUseBase::EquipHornUseBase(const InitArg& arg) : TimeredASPlay(arg) {}

EquipHornUseBase::~EquipHornUseBase() = default;

bool EquipHornUseBase::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void EquipHornUseBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void EquipHornUseBase::leave_() {
    TimeredASPlay::leave_();
}

void EquipHornUseBase::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mSignalOnTime_s, "SignalOnTime");
}

void EquipHornUseBase::calc_() {
    TimeredASPlay::calc_();
}

}  // namespace uking::action
