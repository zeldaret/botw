#include "Game/Actor/Action/actionWarpPlayerToActor.h"

namespace uking::action {

WarpPlayerToActor::WarpPlayerToActor(const InitArg& arg) : DestPlayerWarpBase(arg) {}

WarpPlayerToActor::~WarpPlayerToActor() = default;

bool WarpPlayerToActor::init_(sead::Heap* heap) {
    return DestPlayerWarpBase::init_(heap);
}

void WarpPlayerToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPlayerWarpBase::enter_(params);
}

void WarpPlayerToActor::leave_() {
    DestPlayerWarpBase::leave_();
}

void WarpPlayerToActor::loadParams_() {
    DestPlayerWarpBase::loadParams_();
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
    DestPlayerWarpBase::calc_();
}

}  // namespace uking::action
