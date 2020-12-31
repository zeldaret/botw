#include "Game/AI/AI/aiGuardianMiniBlownOff.h"

namespace uking::ai {

GuardianMiniBlownOff::GuardianMiniBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniBlownOff::~GuardianMiniBlownOff() = default;

bool GuardianMiniBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GuardianMiniBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GuardianMiniBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniBlownOff::loadParams_() {
    getStaticParam(&mRotNeckAngle_s, "RotNeckAngle");
    getStaticParam(&mRotNeckSpeed_s, "RotNeckSpeed");
}

}  // namespace uking::ai
