#include "Game/AI/AI/aiSeqDynamicTimeredTwoAction.h"

namespace uking::ai {

SeqDynamicTimeredTwoAction::SeqDynamicTimeredTwoAction(const InitArg& arg)
    : SeqTimeredTwoAction(arg) {}

SeqDynamicTimeredTwoAction::~SeqDynamicTimeredTwoAction() = default;

void SeqDynamicTimeredTwoAction::loadParams_() {
    SeqTimeredTwoAction::loadParams_();
    getDynamicParam(&mDynFirstActionTime_d, "DynFirstActionTime");
    getDynamicParam(&mDynSecondActionTime_d, "DynSecondActionTime");
    getDynamicParam(&mDynAllActionTime_d, "DynAllActionTime");
}

}  // namespace uking::ai
