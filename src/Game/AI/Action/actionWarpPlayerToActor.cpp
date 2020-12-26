#include "Game/AI/Action/actionWarpPlayerToActor.h"

namespace uking::action {

WarpPlayerToActor::WarpPlayerToActor(const InitArg& arg) : WarpPlayerBase(arg) {}

WarpPlayerToActor::~WarpPlayerToActor() = default;

bool WarpPlayerToActor::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayerToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayerToActor::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayerToActor::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mDestinationX_d, "DestinationX");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mRotToVec3f_d, "RotToVec3f");
    getDynamicParam(&mRelativeDist_d, "RelativeDist");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mOnGround_d, "OnGround");
    getDynamicParam(&mGameDataVec3fRotDir_d, "GameDataVec3fRotDir");
    getDynamicParam(&mIsOffsetBaseTargetActor_d, "IsOffsetBaseTargetActor");
}

void WarpPlayerToActor::calc_() {
    WarpPlayerBase::calc_();
}

}  // namespace uking::action
