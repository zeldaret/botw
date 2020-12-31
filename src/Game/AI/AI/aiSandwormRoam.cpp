#include "Game/AI/AI/aiSandwormRoam.h"

namespace uking::ai {

SandwormRoam::SandwormRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormRoam::~SandwormRoam() = default;

bool SandwormRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormRoam::loadParams_() {
    getStaticParam(&mJumpTimerBase_s, "JumpTimerBase");
    getStaticParam(&mJumpTimerRand_s, "JumpTimerRand");
    getStaticParam(&mJumpDistanceXZ_s, "JumpDistanceXZ");
}

}  // namespace uking::ai
