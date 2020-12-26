#include "Game/AI/Action/actionPlayerSlippingDown.h"

namespace uking::action {

PlayerSlippingDown::PlayerSlippingDown(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PlayerSlippingDown::~PlayerSlippingDown() = default;

bool PlayerSlippingDown::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PlayerSlippingDown::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PlayerSlippingDown::leave_() {
    ksys::act::ai::Action::leave_();
}

void PlayerSlippingDown::loadParams_() {
    getStaticParam(&mDamageInterval_s, "DamageInterval");
    getStaticParam(&mDamageVal_s, "DamageVal");
    getStaticParam(&mChangeableInterval_s, "ChangeableInterval");
    getStaticParam(&mChangeableIntervalInAir_s, "ChangeableIntervalInAir");
    getStaticParam(&mEnableSpeedDamage_s, "EnableSpeedDamage");
    getDynamicParam(&mInitAddLinearImpulse_d, "InitAddLinearImpulse");
    getDynamicParam(&mInitAddRollImpulse_d, "InitAddRollImpulse");
    getDynamicParam(&mIsAddImpulse_d, "IsAddImpulse");
}

void PlayerSlippingDown::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
