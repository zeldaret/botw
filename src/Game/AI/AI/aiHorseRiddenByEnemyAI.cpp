#include "Game/AI/AI/aiHorseRiddenByEnemyAI.h"

namespace uking::ai {

HorseRiddenByEnemyAI::HorseRiddenByEnemyAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRiddenByEnemyAI::~HorseRiddenByEnemyAI() = default;

bool HorseRiddenByEnemyAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenByEnemyAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HorseRiddenByEnemyAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRiddenByEnemyAI::loadParams_() {
    getStaticParam(&mAngryASPeriods_s, "AngryASPeriods");
    getStaticParam(&mFramesRetryNormalActionAtFailed_s, "FramesRetryNormalActionAtFailed");
}

}  // namespace uking::ai
