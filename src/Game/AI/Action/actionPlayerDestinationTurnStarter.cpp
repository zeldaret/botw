#include "Game/AI/Action/actionPlayerDestinationTurnStarter.h"

namespace uking::action {

PlayerDestinationTurnStarter::PlayerDestinationTurnStarter(const InitArg& arg)
    : PlayerAction(arg) {}

PlayerDestinationTurnStarter::~PlayerDestinationTurnStarter() = default;

bool PlayerDestinationTurnStarter::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDestinationTurnStarter::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDestinationTurnStarter::leave_() {
    PlayerAction::leave_();
}

void PlayerDestinationTurnStarter::loadParams_() {}

void PlayerDestinationTurnStarter::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
