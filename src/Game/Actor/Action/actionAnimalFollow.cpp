#include "Game/Actor/Action/actionAnimalFollow.h"

namespace uking::action {

AnimalFollow::AnimalFollow(const InitArg& arg) : HorseFollowBase(arg) {}

AnimalFollow::~AnimalFollow() = default;

bool AnimalFollow::init_(sead::Heap* heap) {
    return HorseFollowBase::init_(heap);
}

void AnimalFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollowBase::enter_(params);
}

void AnimalFollow::leave_() {
    HorseFollowBase::leave_();
}

void AnimalFollow::loadParams_() {
    HorseFollowBase::loadParams_();
    getStaticParam(&mDistanceKept_s, "DistanceKept");
}

void AnimalFollow::calc_() {
    HorseFollowBase::calc_();
}

}  // namespace uking::action
