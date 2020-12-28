#include "Game/AI/Action/actionPlayerSetVisibleWeapon.h"

namespace uking::action {

PlayerSetVisibleWeapon::PlayerSetVisibleWeapon(const InitArg& arg) : PlayerAction(arg) {}

PlayerSetVisibleWeapon::~PlayerSetVisibleWeapon() = default;

bool PlayerSetVisibleWeapon::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSetVisibleWeapon::loadParams_() {
    getDynamicParam(&mSetVisible_d, "SetVisible");
}

}  // namespace uking::action
