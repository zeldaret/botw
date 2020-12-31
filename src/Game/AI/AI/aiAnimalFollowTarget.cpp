#include "Game/AI/AI/aiAnimalFollowTarget.h"

namespace uking::ai {

AnimalFollowTarget::AnimalFollowTarget(const InitArg& arg) : HorseFollow(arg) {}

AnimalFollowTarget::~AnimalFollowTarget() = default;

bool AnimalFollowTarget::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

void AnimalFollowTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void AnimalFollowTarget::leave_() {
    HorseFollow::leave_();
}

void AnimalFollowTarget::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mUseLocalOffsetType_s, "UseLocalOffsetType");
}

}  // namespace uking::ai
