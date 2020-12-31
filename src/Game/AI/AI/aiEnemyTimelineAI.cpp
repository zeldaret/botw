#include "Game/AI/AI/aiEnemyTimelineAI.h"

namespace uking::ai {

EnemyTimelineAI::EnemyTimelineAI(const InitArg& arg) : TimelineAI(arg) {}

EnemyTimelineAI::~EnemyTimelineAI() = default;

bool EnemyTimelineAI::init_(sead::Heap* heap) {
    return TimelineAI::init_(heap);
}

void EnemyTimelineAI::enter_(ksys::act::ai::InlineParamPack* params) {
    TimelineAI::enter_(params);
}

void EnemyTimelineAI::leave_() {
    TimelineAI::leave_();
}

void EnemyTimelineAI::loadParams_() {
    TimelineAI::loadParams_();
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
