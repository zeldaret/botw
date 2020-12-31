#include "Game/AI/AI/aiAnchorRangeSelectTwoAction.h"

namespace uking::ai {

AnchorRangeSelectTwoAction::AnchorRangeSelectTwoAction(const InitArg& arg)
    : RangeSelectTwoAction(arg) {}

AnchorRangeSelectTwoAction::~AnchorRangeSelectTwoAction() = default;

bool AnchorRangeSelectTwoAction::init_(sead::Heap* heap) {
    return RangeSelectTwoAction::init_(heap);
}

void AnchorRangeSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelectTwoAction::enter_(params);
}

void AnchorRangeSelectTwoAction::leave_() {
    RangeSelectTwoAction::leave_();
}

void AnchorRangeSelectTwoAction::loadParams_() {
    RangeSelectTwoAction::loadParams_();
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mAnchorName_s, "AnchorName");
}

}  // namespace uking::ai
