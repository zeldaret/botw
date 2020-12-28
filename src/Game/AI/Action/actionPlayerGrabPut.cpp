#include "Game/AI/Action/actionPlayerGrabPut.h"

namespace uking::action {

PlayerGrabPut::PlayerGrabPut(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabPut::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabPut::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabPut::loadParams_() {
    getStaticParam(&mPutStartFrmae_s, "PutStartFrmae");
}

void PlayerGrabPut::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
