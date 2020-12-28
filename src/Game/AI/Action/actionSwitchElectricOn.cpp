#include "Game/AI/Action/actionSwitchElectricOn.h"

namespace uking::action {

SwitchElectricOn::SwitchElectricOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool SwitchElectricOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchElectricOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchElectricOn::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchElectricOn::loadParams_() {
    getStaticParam(&mElecReq_s, "ElecReq");
    getStaticParam(&mVolReq_s, "VolReq");
    getStaticParam(&mTargetVol_s, "TargetVol");
    getStaticParam(&mMinEnergyRate_s, "MinEnergyRate");
    getStaticParam(&mUseSklAnm_s, "UseSklAnm");
}

void SwitchElectricOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
