#include "Game/AI/AI/aiRailMoveWithClose.h"

namespace uking::ai {

RailMoveWithClose::RailMoveWithClose(const InitArg& arg) : RailMove(arg) {}

RailMoveWithClose::~RailMoveWithClose() = default;

bool RailMoveWithClose::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void RailMoveWithClose::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMove::enter_(params);
}

void RailMoveWithClose::leave_() {
    RailMove::leave_();
}

void RailMoveWithClose::loadParams_() {
    RailMove::loadParams_();
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mSpeed_s, "Speed");
}

}  // namespace uking::ai
