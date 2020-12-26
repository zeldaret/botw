#include "Game/AI/Action/actionRemainElectricCannonCharge.h"

namespace uking::action {

RemainElectricCannonCharge::RemainElectricCannonCharge(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonCharge::~RemainElectricCannonCharge() = default;

bool RemainElectricCannonCharge::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonCharge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainElectricCannonCharge::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainElectricCannonCharge::loadParams_() {
    getStaticParam(&mChargeTime_s, "ChargeTime");
}

void RemainElectricCannonCharge::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
