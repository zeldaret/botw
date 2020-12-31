#include "Game/AI/AI/aiRailMoveRndIgnrStopPlayAS.h"

namespace uking::ai {

RailMoveRndIgnrStopPlayAS::RailMoveRndIgnrStopPlayAS(const InitArg& arg)
    : RailMoveRandomIgnoreStop(arg) {}

RailMoveRndIgnrStopPlayAS::~RailMoveRndIgnrStopPlayAS() = default;

bool RailMoveRndIgnrStopPlayAS::init_(sead::Heap* heap) {
    return RailMoveRandomIgnoreStop::init_(heap);
}

void RailMoveRndIgnrStopPlayAS::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRandomIgnoreStop::enter_(params);
}

void RailMoveRndIgnrStopPlayAS::leave_() {
    RailMoveRandomIgnoreStop::leave_();
}

void RailMoveRndIgnrStopPlayAS::loadParams_() {
    RailMoveRandomIgnoreStop::loadParams_();
}

}  // namespace uking::ai
