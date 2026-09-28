#include "Game/Actor/AI/aiTargetHomeRangeSelect.h"

namespace uking::ai {

TargetHomeRangeSelect::TargetHomeRangeSelect(const InitArg& arg) : NewRangeSelect(arg) {}

TargetHomeRangeSelect::~TargetHomeRangeSelect() = default;

bool TargetHomeRangeSelect::init_(sead::Heap* heap) {
    return NewRangeSelect::init_(heap);
}

void TargetHomeRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    NewRangeSelect::enter_(params);
}

void TargetHomeRangeSelect::leave_() {
    NewRangeSelect::leave_();
}

void TargetHomeRangeSelect::loadParams_() {
    NewRangeSelect::loadParams_();
}

}  // namespace uking::ai
