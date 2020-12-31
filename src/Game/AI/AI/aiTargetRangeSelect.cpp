#include "Game/AI/AI/aiTargetRangeSelect.h"

namespace uking::ai {

TargetRangeSelect::TargetRangeSelect(const InitArg& arg) : RangeSelect(arg) {}

TargetRangeSelect::~TargetRangeSelect() = default;

void TargetRangeSelect::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mIsXZOnly_s, "IsXZOnly");
}

}  // namespace uking::ai
