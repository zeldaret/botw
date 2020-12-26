#include "Game/AI/Action/actionPlayerBeetleSubject.h"

namespace uking::action {

PlayerBeetleSubject::PlayerBeetleSubject(const InitArg& arg) : PlayerAction(arg) {}

PlayerBeetleSubject::~PlayerBeetleSubject() = default;

bool PlayerBeetleSubject::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerBeetleSubject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBeetleSubject::leave_() {
    PlayerAction::leave_();
}

void PlayerBeetleSubject::loadParams_() {
    getStaticParam(&mAimRange_s, "AimRange");
}

void PlayerBeetleSubject::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
