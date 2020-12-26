#include "Game/AI/Action/actionPlayerSwitchHang.h"

namespace uking::action {

PlayerSwitchHang::PlayerSwitchHang(const InitArg& arg) : PlayerAction(arg) {}

PlayerSwitchHang::~PlayerSwitchHang() = default;

bool PlayerSwitchHang::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSwitchHang::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwitchHang::leave_() {
    PlayerAction::leave_();
}

void PlayerSwitchHang::loadParams_() {}

void PlayerSwitchHang::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
