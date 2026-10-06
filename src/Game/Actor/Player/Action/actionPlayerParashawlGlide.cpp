#include "Game/Actor/Player/Action/actionPlayerParashawlGlide.h"

namespace uking::action {

PlayerParashawlGlide::PlayerParashawlGlide(const InitArg& arg) : PlayerParashawlGlideBase(arg) {}

void PlayerParashawlGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerParashawlGlideBase::enter_(params);
}

void PlayerParashawlGlide::leave_() {
    PlayerParashawlGlideBase::leave_();
}

void PlayerParashawlGlide::loadParams_() {
    PlayerParashawlGlideBase::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerParashawlGlide::calc_() {
    PlayerParashawlGlideBase::calc_();
}

}  // namespace uking::action
