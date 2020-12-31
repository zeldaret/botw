#include "Game/AI/AI/aiRangeLineReachSelectTwoAction.h"

namespace uking::ai {

RangeLineReachSelectTwoAction::RangeLineReachSelectTwoAction(const InitArg& arg)
    : RangeSelectTwoAction(arg) {}

RangeLineReachSelectTwoAction::~RangeLineReachSelectTwoAction() = default;

bool RangeLineReachSelectTwoAction::init_(sead::Heap* heap) {
    return RangeSelectTwoAction::init_(heap);
}

void RangeLineReachSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelectTwoAction::enter_(params);
}

void RangeLineReachSelectTwoAction::leave_() {
    RangeSelectTwoAction::leave_();
}

void RangeLineReachSelectTwoAction::loadParams_() {
    RangeSelectTwoAction::loadParams_();
}

}  // namespace uking::ai
