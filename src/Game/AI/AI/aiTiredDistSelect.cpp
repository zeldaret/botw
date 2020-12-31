#include "Game/AI/AI/aiTiredDistSelect.h"

namespace uking::ai {

TiredDistSelect::TiredDistSelect(const InitArg& arg) : TargetHomeRangeSelect(arg) {}

TiredDistSelect::~TiredDistSelect() = default;

bool TiredDistSelect::init_(sead::Heap* heap) {
    return TargetHomeRangeSelect::init_(heap);
}

void TiredDistSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetHomeRangeSelect::enter_(params);
}

void TiredDistSelect::leave_() {
    TargetHomeRangeSelect::leave_();
}

void TiredDistSelect::loadParams_() {
    TargetHomeRangeSelect::loadParams_();
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

}  // namespace uking::ai
