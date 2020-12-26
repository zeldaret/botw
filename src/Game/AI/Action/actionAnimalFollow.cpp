#include "Game/AI/Action/actionAnimalFollow.h"

namespace uking::action {

AnimalFollow::AnimalFollow(const InitArg& arg) : AnimalFollowBase(arg) {}

AnimalFollow::~AnimalFollow() = default;

bool AnimalFollow::init_(sead::Heap* heap) {
    return AnimalFollowBase::init_(heap);
}

void AnimalFollow::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalFollowBase::enter_(params);
}

void AnimalFollow::leave_() {
    AnimalFollowBase::leave_();
}

void AnimalFollow::loadParams_() {
    AnimalFollowBase::loadParams_();
    getStaticParam(&mDistanceKept_s, "DistanceKept");
}

void AnimalFollow::calc_() {
    AnimalFollowBase::calc_();
}

}  // namespace uking::action
