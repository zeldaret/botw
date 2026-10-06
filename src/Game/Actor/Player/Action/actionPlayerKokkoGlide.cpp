#include "Game/Actor/Player/Action/actionPlayerKokkoGlide.h"

namespace uking::action {

PlayerKokkoGlide::PlayerKokkoGlide(const InitArg& arg) : PlayerParashawlGlideBase(arg) {}

void PlayerKokkoGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerParashawlGlideBase::enter_(params);
}

void PlayerKokkoGlide::leave_() {
    PlayerParashawlGlideBase::leave_();
}

void PlayerKokkoGlide::loadParams_() {
    PlayerParashawlGlideBase::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerKokkoGlide::calc_() {
    PlayerParashawlGlideBase::calc_();
}

}  // namespace uking::action
