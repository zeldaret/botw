#include "Game/AI/AI/aiHorseLoopTarget.h"

namespace uking::ai {

HorseLoopTarget::HorseLoopTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseLoopTarget::~HorseLoopTarget() = default;

void HorseLoopTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseLoopTarget::loadParams_() {
    getStaticParam(&mTargetName_s, "TargetName");
    getStaticParam(&mIsFlip_s, "IsFlip");
}

}  // namespace uking::ai
