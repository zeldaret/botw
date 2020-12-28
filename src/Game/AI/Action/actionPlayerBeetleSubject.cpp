#include "Game/AI/Action/actionPlayerBeetleSubject.h"

namespace uking::action {

PlayerBeetleSubject::PlayerBeetleSubject(const InitArg& arg) : PlayerAction(arg) {}

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
