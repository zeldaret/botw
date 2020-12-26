#include "Game/AI/Action/actionPlayerLookAtObjectNow.h"

namespace uking::action {

PlayerLookAtObjectNow::PlayerLookAtObjectNow(const InitArg& arg) : PlayerLookAtObject(arg) {}

PlayerLookAtObjectNow::~PlayerLookAtObjectNow() = default;

bool PlayerLookAtObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObject::init_(heap);
}

void PlayerLookAtObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerLookAtObject::enter_(params);
}

void PlayerLookAtObjectNow::leave_() {
    PlayerLookAtObject::leave_();
}

void PlayerLookAtObjectNow::loadParams_() {
    PlayerLookAtObject::loadParams_();
}

void PlayerLookAtObjectNow::calc_() {
    PlayerLookAtObject::calc_();
}

}  // namespace uking::action
