#include "Game/AI/Action/actionPlayerWakeBoardReady.h"

namespace uking::action {

PlayerWakeBoardReady::PlayerWakeBoardReady(const InitArg& arg) : PlayerAction(arg) {}

PlayerWakeBoardReady::~PlayerWakeBoardReady() = default;

void PlayerWakeBoardReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWakeBoardReady::leave_() {
    PlayerAction::leave_();
}

void PlayerWakeBoardReady::loadParams_() {
    getDynamicParam(&mCreateSelf_d, "CreateSelf");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void PlayerWakeBoardReady::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
