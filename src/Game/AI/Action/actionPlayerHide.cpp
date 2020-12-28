#include "Game/AI/Action/actionPlayerHide.h"

namespace uking::action {

PlayerHide::PlayerHide(const InitArg& arg) : PlayerAction(arg) {}

PlayerHide::~PlayerHide() = default;

bool PlayerHide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerHide::loadParams_() {
    getStaticParam(&mHidden_s, "Hidden");
}

}  // namespace uking::action
