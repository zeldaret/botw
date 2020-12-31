#include "Game/AI/AI/aiRailMoveRandomIgnoreStop.h"

namespace uking::ai {

RailMoveRandomIgnoreStop::RailMoveRandomIgnoreStop(const InitArg& arg) : RailMoveWithClose(arg) {}

RailMoveRandomIgnoreStop::~RailMoveRandomIgnoreStop() = default;

bool RailMoveRandomIgnoreStop::init_(sead::Heap* heap) {
    return RailMoveWithClose::init_(heap);
}

void RailMoveRandomIgnoreStop::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveWithClose::enter_(params);
}

void RailMoveRandomIgnoreStop::leave_() {
    RailMoveWithClose::leave_();
}

void RailMoveRandomIgnoreStop::loadParams_() {
    RailMoveWithClose::loadParams_();
    getStaticParam(&mStopRate_s, "StopRate");
}

}  // namespace uking::ai
