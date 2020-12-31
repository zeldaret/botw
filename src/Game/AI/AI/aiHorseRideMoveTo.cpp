#include "Game/AI/AI/aiHorseRideMoveTo.h"

namespace uking::ai {

HorseRideMoveTo::HorseRideMoveTo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideMoveTo::~HorseRideMoveTo() = default;

bool HorseRideMoveTo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideMoveTo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRideMoveTo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideMoveTo::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
