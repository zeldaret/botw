#include "Game/Actor/AI/aiRailMoveWithClose.h"

namespace uking::ai {

RailMoveWithClose::RailMoveWithClose(const InitArg& arg) : BezierRailMove(arg) {}

RailMoveWithClose::~RailMoveWithClose() = default;

bool RailMoveWithClose::init_(sead::Heap* heap) {
    return BezierRailMove::init_(heap);
}

void RailMoveWithClose::enter_(ksys::act::ai::InlineParamPack* params) {
    BezierRailMove::enter_(params);
}

void RailMoveWithClose::leave_() {
    BezierRailMove::leave_();
}

void RailMoveWithClose::loadParams_() {
    BezierRailMove::loadParams_();
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
}

}  // namespace uking::ai
