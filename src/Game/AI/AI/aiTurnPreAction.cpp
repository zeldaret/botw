#include "Game/AI/AI/aiTurnPreAction.h"

namespace uking::ai {

TurnPreAction::TurnPreAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TurnPreAction::~TurnPreAction() = default;

void TurnPreAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TurnPreAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TurnPreAction::loadParams_() {
    getStaticParam(&mTurnStartAngle_s, "TurnStartAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
