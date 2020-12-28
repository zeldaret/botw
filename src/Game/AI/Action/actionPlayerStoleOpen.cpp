#include "Game/AI/Action/actionPlayerStoleOpen.h"

namespace uking::action {

PlayerStoleOpen::PlayerStoleOpen(const InitArg& arg) : PlayerStoleOpenEx(arg) {}

void PlayerStoleOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerStoleOpenEx::enter_(params);
}

void PlayerStoleOpen::loadParams_() {
    PlayerStoleOpenBase::loadParams_();
    getStaticParam(&mEnlargeSpd_s, "EnlargeSpd");
}

void PlayerStoleOpen::calc_() {
    PlayerStoleOpenEx::calc_();
}

}  // namespace uking::action
