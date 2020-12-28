#include "Game/AI/Action/actionPlayerLookAtObjectNow.h"

namespace uking::action {

PlayerLookAtObjectNow::PlayerLookAtObjectNow(const InitArg& arg) : PlayerLookAtObject(arg) {}

PlayerLookAtObjectNow::~PlayerLookAtObjectNow() = default;

bool PlayerLookAtObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObject::init_(heap);
}

void PlayerLookAtObjectNow::loadParams_() {
    PlayerLookAtObject::loadParams_();
}

}  // namespace uking::action
