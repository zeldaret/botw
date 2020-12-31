#include "Game/AI/AI/aiRangeSelectTwoAction.h"

namespace uking::ai {

RangeSelectTwoAction::RangeSelectTwoAction(const InitArg& arg) : RangeSelectAction(arg) {}

RangeSelectTwoAction::~RangeSelectTwoAction() = default;

void RangeSelectTwoAction::loadParams_() {
    RangeSelectAction::loadParams_();
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
}

}  // namespace uking::ai
