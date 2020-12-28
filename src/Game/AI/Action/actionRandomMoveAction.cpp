#include "Game/AI/Action/actionRandomMoveAction.h"

namespace uking::action {

RandomMoveAction::RandomMoveAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RandomMoveAction::~RandomMoveAction() = default;

void RandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RandomMoveAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void RandomMoveAction::loadParams_() {
    getStaticParam(&mIsSuccessWhenGoalReached_s, "IsSuccessWhenGoalReached");
}

void RandomMoveAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
