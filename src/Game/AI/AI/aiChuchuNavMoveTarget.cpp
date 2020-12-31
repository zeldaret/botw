#include "Game/AI/AI/aiChuchuNavMoveTarget.h"

namespace uking::ai {

ChuchuNavMoveTarget::ChuchuNavMoveTarget(const InitArg& arg) : NavMoveTarget(arg) {}

ChuchuNavMoveTarget::~ChuchuNavMoveTarget() = default;

bool ChuchuNavMoveTarget::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void ChuchuNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
}

void ChuchuNavMoveTarget::leave_() {
    NavMoveTarget::leave_();
}

void ChuchuNavMoveTarget::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mWallHitTime_s, "WallHitTime");
}

}  // namespace uking::ai
