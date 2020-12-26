#include "Game/AI/Action/actionAnimalFollowBase.h"

namespace uking::action {

AnimalFollowBase::AnimalFollowBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalFollowBase::~AnimalFollowBase() = default;

bool AnimalFollowBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalFollowBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimalFollowBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalFollowBase::loadParams_() {
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mWaitDistanceToLeader_s, "WaitDistanceToLeader");
    getStaticParam(&mGear1DistanceToLeader_s, "Gear1DistanceToLeader");
    getStaticParam(&mGear2DistanceToLeader_s, "Gear2DistanceToLeader");
    getStaticParam(&mGear3DistanceToLeader_s, "Gear3DistanceToLeader");
    getStaticParam(&mDistanceFactorAtGearDown_s, "DistanceFactorAtGearDown");
    getStaticParam(&mWaitDistanceIncreaseDistance_s, "WaitDistanceIncreaseDistance");
    getStaticParam(&mWaitDistanceIncreasePerFrame_s, "WaitDistanceIncreasePerFrame");
    getStaticParam(&mAutoStopAndTurnDistance_s, "AutoStopAndTurnDistance");
    getStaticParam(&mDesiredDirAngleDeltaSecMax_s, "DesiredDirAngleDeltaSecMax");
    getStaticParam(&mNavMeshCharacterRadiusScale_s, "NavMeshCharacterRadiusScale");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mIsEndAtAutoStop_s, "IsEndAtAutoStop");
    getStaticParam(&mUseMinRadius_s, "UseMinRadius");
    getStaticParam(&mIsAvoidNavMeshActor_s, "IsAvoidNavMeshActor");
    getStaticParam(&mIsTargetPosEqualToLeaderPos_s, "IsTargetPosEqualToLeaderPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalFollowBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
