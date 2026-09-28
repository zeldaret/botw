#include "Game/Actor/AI/aiTargetRangeSelect.h"

namespace uking::ai {

TargetRangeSelect::TargetRangeSelect(const InitArg& arg) : NewRangeSelect(arg) {}

TargetRangeSelect::~TargetRangeSelect() = default;

void TargetRangeSelect::loadParams_() {
    NewRangeSelect::loadParams_();
    getStaticParam(&mIsXZOnly_s, "IsXZOnly");
}

}  // namespace uking::ai
