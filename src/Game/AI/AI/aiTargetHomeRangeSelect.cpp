#include "Game/AI/AI/aiTargetHomeRangeSelect.h"

namespace uking::ai {

TargetHomeRangeSelect::TargetHomeRangeSelect(const InitArg& arg) : RangeSelect(arg) {}

TargetHomeRangeSelect::~TargetHomeRangeSelect() = default;

bool TargetHomeRangeSelect::init_(sead::Heap* heap) {
    return RangeSelect::init_(heap);
}

void TargetHomeRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void TargetHomeRangeSelect::leave_() {
    RangeSelect::leave_();
}

void TargetHomeRangeSelect::loadParams_() {
    RangeSelect::loadParams_();
}

}  // namespace uking::ai
