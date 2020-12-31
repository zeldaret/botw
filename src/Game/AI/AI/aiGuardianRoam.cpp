#include "Game/AI/AI/aiGuardianRoam.h"

namespace uking::ai {

GuardianRoam::GuardianRoam(const InitArg& arg) : GuardianAI(arg) {}

GuardianRoam::~GuardianRoam() = default;

bool GuardianRoam::init_(sead::Heap* heap) {
    return GuardianAI::init_(heap);
}

void GuardianRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAI::enter_(params);
}

void GuardianRoam::leave_() {
    GuardianAI::leave_();
}

void GuardianRoam::loadParams_() {
    GuardianAI::loadParams_();
    getStaticParam(&mMoveTime_s, "MoveTime");
    getStaticParam(&mMoveRadius_s, "MoveRadius");
}

}  // namespace uking::ai
