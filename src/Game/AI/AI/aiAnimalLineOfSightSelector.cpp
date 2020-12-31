#include "Game/AI/AI/aiAnimalLineOfSightSelector.h"

namespace uking::ai {

AnimalLineOfSightSelector::AnimalLineOfSightSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalLineOfSightSelector::~AnimalLineOfSightSelector() = default;

bool AnimalLineOfSightSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalLineOfSightSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalLineOfSightSelector::loadParams_() {
    getStaticParam(&mStartGear_s, "StartGear");
    getStaticParam(&mMinGear_s, "MinGear");
    getStaticParam(&mMaxGear_s, "MaxGear");
    getStaticParam(&mGearUpRestrictionFrames_s, "GearUpRestrictionFrames");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
