#include "Game/AI/AI/aiRangeSelectThreeAction.h"

namespace uking::ai {

RangeSelectThreeAction::RangeSelectThreeAction(const InitArg& arg) : RangeSelectAction(arg) {}

RangeSelectThreeAction::~RangeSelectThreeAction() = default;

void RangeSelectThreeAction::loadParams_() {
    RangeSelectAction::loadParams_();
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
}

}  // namespace uking::ai
