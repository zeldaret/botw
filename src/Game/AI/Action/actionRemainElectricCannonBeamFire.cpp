#include "Game/AI/Action/actionRemainElectricCannonBeamFire.h"

namespace uking::action {

RemainElectricCannonBeamFire::RemainElectricCannonBeamFire(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonBeamFire::~RemainElectricCannonBeamFire() = default;

bool RemainElectricCannonBeamFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonBeamFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainElectricCannonBeamFire::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainElectricCannonBeamFire::loadParams_() {
    getStaticParam(&mAtkDamage_s, "AtkDamage");
    getStaticParam(&mMinDamage_s, "MinDamage");
    getDynamicParam(&mIsProtected_d, "IsProtected");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mSafePos_d, "SafePos");
}

void RemainElectricCannonBeamFire::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
