#include "Game/AI/Action/actionHorseFollow.h"

namespace uking::action {

HorseFollow::HorseFollow(const InitArg& arg) : AnimalFollowBase(arg) {}

HorseFollow::~HorseFollow() = default;

bool HorseFollow::init_(sead::Heap* heap) {
    return AnimalFollowBase::init_(heap);
}

void HorseFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalFollowBase::enter_(params);
}

void HorseFollow::leave_() {
    AnimalFollowBase::leave_();
}

void HorseFollow::loadParams_() {
    AnimalFollowBase::loadParams_();
    getDynamicParam(&mDistanceKept_d, "DistanceKept");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseFollow::calc_() {
    AnimalFollowBase::calc_();
}

}  // namespace uking::action
