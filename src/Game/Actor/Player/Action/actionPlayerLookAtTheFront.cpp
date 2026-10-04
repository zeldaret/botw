#include "Game/Actor/Player/Action/actionPlayerLookAtTheFront.h"

namespace uking::action {

PlayerLookAtTheFront::PlayerLookAtTheFront(const InitArg& arg) : PlayerAction(arg) {}

PlayerLookAtTheFront::~PlayerLookAtTheFront() = default;

bool PlayerLookAtTheFront::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLookAtTheFront::loadParams_() {
    getDynamicParam(&mIsValid_d, "IsValid");
}

}  // namespace uking::action
