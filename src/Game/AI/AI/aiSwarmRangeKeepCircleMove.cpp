#include "Game/AI/AI/aiSwarmRangeKeepCircleMove.h"

namespace uking::ai {

SwarmRangeKeepCircleMove::SwarmRangeKeepCircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SwarmRangeKeepCircleMove::~SwarmRangeKeepCircleMove() = default;

bool SwarmRangeKeepCircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SwarmRangeKeepCircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SwarmRangeKeepCircleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SwarmRangeKeepCircleMove::loadParams_() {
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mUpdateCircleMoveDistance_s, "UpdateCircleMoveDistance");
}

}  // namespace uking::ai
