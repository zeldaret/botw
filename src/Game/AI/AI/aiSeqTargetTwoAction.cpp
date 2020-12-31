#include "Game/AI/AI/aiSeqTargetTwoAction.h"

namespace uking::ai {

SeqTargetTwoAction::SeqTargetTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void SeqTargetTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqTargetTwoAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
