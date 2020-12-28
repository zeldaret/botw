#include "Game/AI/Action/actionPlayerIceBlockRemove.h"

namespace uking::action {

PlayerIceBlockRemove::PlayerIceBlockRemove(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceBlockRemove::~PlayerIceBlockRemove() = default;

void PlayerIceBlockRemove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIceBlockRemove::leave_() {
    PlayerAction::leave_();
}

void PlayerIceBlockRemove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
