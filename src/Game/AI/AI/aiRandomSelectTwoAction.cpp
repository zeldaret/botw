#include "Game/AI/AI/aiRandomSelectTwoAction.h"

namespace uking::ai {

RandomSelectTwoAction::RandomSelectTwoAction(const InitArg& arg) : RandomSelectTwoActionBase(arg) {}

RandomSelectTwoAction::~RandomSelectTwoAction() = default;

void RandomSelectTwoAction::loadParams_() {
    RandomSelectTwoActionBase::loadParams_();
    getStaticParam(&mTransitionRateToA_s, "TransitionRateToA");
}

}  // namespace uking::ai
