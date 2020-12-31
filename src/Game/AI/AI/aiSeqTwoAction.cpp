#include "Game/AI/AI/aiSeqTwoAction.h"

namespace uking::ai {

SeqTwoAction::SeqTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void SeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqTwoAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
    getStaticParam(&mIsNoChangeable_s, "IsNoChangeable");
}

}  // namespace uking::ai
