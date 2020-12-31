#include "Game/AI/AI/aiRailMoveRemainsBGCamera.h"

namespace uking::ai {

RailMoveRemainsBGCamera::RailMoveRemainsBGCamera(const InitArg& arg) : RailMoveRemains(arg) {}

RailMoveRemainsBGCamera::~RailMoveRemainsBGCamera() = default;

bool RailMoveRemainsBGCamera::init_(sead::Heap* heap) {
    return RailMoveRemains::init_(heap);
}

void RailMoveRemainsBGCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    RailMoveRemains::enter_(params);
}

void RailMoveRemainsBGCamera::leave_() {
    RailMoveRemains::leave_();
}

void RailMoveRemainsBGCamera::loadParams_() {
    RailMoveRemains::loadParams_();
    getStaticParam(&mIsAllowRotAxisX_s, "IsAllowRotAxisX");
    getStaticParam(&mDungeonName_s, "DungeonName");
    getStaticParam(&mRailName_s, "RailName");
}

}  // namespace uking::ai
