#include "Game/AI/Action/actionPlayerParashawlGlide.h"

namespace uking::action {

PlayerParashawlGlide::PlayerParashawlGlide(const InitArg& arg) : PlayerGlide(arg) {}

void PlayerParashawlGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGlide::enter_(params);
}

void PlayerParashawlGlide::leave_() {
    PlayerGlide::leave_();
}

void PlayerParashawlGlide::loadParams_() {
    PlayerGlide::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerParashawlGlide::calc_() {
    PlayerGlide::calc_();
}

}  // namespace uking::action
