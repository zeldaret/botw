#include "Game/AI/Action/actionPlayerStoleOpen.h"

namespace uking::action {

PlayerStoleOpen::PlayerStoleOpen(const InitArg& arg) : PlayerStoleOpenEx(arg) {}

PlayerStoleOpen::~PlayerStoleOpen() = default;

bool PlayerStoleOpen::init_(sead::Heap* heap) {
    return PlayerStoleOpenEx::init_(heap);
}

void PlayerStoleOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerStoleOpenEx::enter_(params);
}

void PlayerStoleOpen::leave_() {
    PlayerStoleOpenEx::leave_();
}

void PlayerStoleOpen::loadParams_() {
    PlayerStoleOpenBase::loadParams_();
    getStaticParam(&mEnlargeSpd_s, "EnlargeSpd");
}

void PlayerStoleOpen::calc_() {
    PlayerStoleOpenEx::calc_();
}

}  // namespace uking::action
