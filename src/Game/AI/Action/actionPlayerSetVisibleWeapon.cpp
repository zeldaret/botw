#include "Game/AI/Action/actionPlayerSetVisibleWeapon.h"

namespace uking::action {

PlayerSetVisibleWeapon::PlayerSetVisibleWeapon(const InitArg& arg) : PlayerAction(arg) {}

PlayerSetVisibleWeapon::~PlayerSetVisibleWeapon() = default;

bool PlayerSetVisibleWeapon::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSetVisibleWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSetVisibleWeapon::leave_() {
    PlayerAction::leave_();
}

void PlayerSetVisibleWeapon::loadParams_() {
    getDynamicParam(&mSetVisible_d, "SetVisible");
}

void PlayerSetVisibleWeapon::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
