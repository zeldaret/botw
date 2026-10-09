#include "Game/Actor/Action/actionHorseFollow.h"

namespace uking::action {

HorseFollow::HorseFollow(const InitArg& arg) : HorseFollowBase(arg) {}

HorseFollow::~HorseFollow() = default;

bool HorseFollow::init_(sead::Heap* heap) {
    return HorseFollowBase::init_(heap);
}

void HorseFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollowBase::enter_(params);
}

void HorseFollow::leave_() {
    HorseFollowBase::leave_();
}

void HorseFollow::loadParams_() {
    HorseFollowBase::loadParams_();
    getDynamicParam(&mDistanceKept_d, "DistanceKept");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseFollow::calc_() {
    HorseFollowBase::calc_();
}

}  // namespace uking::action
