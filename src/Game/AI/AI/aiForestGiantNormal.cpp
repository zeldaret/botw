#include "Game/AI/AI/aiForestGiantNormal.h"

namespace uking::ai {

ForestGiantNormal::ForestGiantNormal(const InitArg& arg) : EnemyNormal(arg) {}

ForestGiantNormal::~ForestGiantNormal() = default;

bool ForestGiantNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void ForestGiantNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void ForestGiantNormal::leave_() {
    EnemyNormal::leave_();
}

void ForestGiantNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSleepingHearAwnRatio_s, "SleepingHearAwnRatio");
}

}  // namespace uking::ai
