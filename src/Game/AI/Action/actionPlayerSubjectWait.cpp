#include "Game/AI/Action/actionPlayerSubjectWait.h"

namespace uking::action {

PlayerSubjectWait::PlayerSubjectWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerSubjectWait::~PlayerSubjectWait() = default;

bool PlayerSubjectWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSubjectWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSubjectWait::leave_() {
    PlayerAction::leave_();
}

void PlayerSubjectWait::loadParams_() {}

void PlayerSubjectWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
