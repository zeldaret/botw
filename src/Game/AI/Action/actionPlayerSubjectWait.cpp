#include "Game/AI/Action/actionPlayerSubjectWait.h"

namespace uking::action {

PlayerSubjectWait::PlayerSubjectWait(const InitArg& arg) : PlayerAction(arg) {}

void PlayerSubjectWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSubjectWait::leave_() {
    PlayerAction::leave_();
}

void PlayerSubjectWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
