#include "Game/Actor/AI/aiTargetHeightAreaSelect.h"

namespace uking::ai {

TargetHeightAreaSelect::TargetHeightAreaSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

TargetHeightAreaSelect::~TargetHeightAreaSelect() = default;

bool TargetHeightAreaSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

void TargetHeightAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void TargetHeightAreaSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void TargetHeightAreaSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mHeight_s, "Height");
}

}  // namespace uking::ai
