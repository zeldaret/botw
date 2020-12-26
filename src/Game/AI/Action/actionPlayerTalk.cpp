#include "Game/AI/Action/actionPlayerTalk.h"

namespace uking::action {

PlayerTalk::PlayerTalk(const InitArg& arg) : PlayerAction(arg) {}

PlayerTalk::~PlayerTalk() = default;

bool PlayerTalk::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerTalk::leave_() {
    PlayerAction::leave_();
}

void PlayerTalk::loadParams_() {
    getDynamicParam(&mGreetingType_d, "GreetingType");
}

void PlayerTalk::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
