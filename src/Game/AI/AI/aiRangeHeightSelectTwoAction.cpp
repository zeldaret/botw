#include "Game/AI/AI/aiRangeHeightSelectTwoAction.h"

namespace uking::ai {

RangeHeightSelectTwoAction::RangeHeightSelectTwoAction(const InitArg& arg)
    : RangeSelectTwoAction(arg) {}

RangeHeightSelectTwoAction::~RangeHeightSelectTwoAction() = default;

bool RangeHeightSelectTwoAction::init_(sead::Heap* heap) {
    return RangeSelectTwoAction::init_(heap);
}

void RangeHeightSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelectTwoAction::enter_(params);
}

void RangeHeightSelectTwoAction::leave_() {
    RangeSelectTwoAction::leave_();
}

void RangeHeightSelectTwoAction::loadParams_() {
    RangeSelectTwoAction::loadParams_();
    getStaticParam(&mMaxY_s, "MaxY");
    getStaticParam(&mMinY_s, "MinY");
}

}  // namespace uking::ai
