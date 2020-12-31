#include "Game/AI/AI/aiTargetElevationGapSelect.h"

namespace uking::ai {

TargetElevationGapSelect::TargetElevationGapSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetElevationGapSelect::~TargetElevationGapSelect() = default;

bool TargetElevationGapSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetElevationGapSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetElevationGapSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetElevationGapSelect::loadParams_() {
    getStaticParam(&mElvGap_s, "ElvGap");
}

}  // namespace uking::ai
