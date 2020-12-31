#include "Game/AI/AI/aiKakarikoKokkoTimeline.h"

namespace uking::ai {

KakarikoKokkoTimeline::KakarikoKokkoTimeline(const InitArg& arg) : AnimalTimelineAI(arg) {}

KakarikoKokkoTimeline::~KakarikoKokkoTimeline() = default;

bool KakarikoKokkoTimeline::init_(sead::Heap* heap) {
    return AnimalTimelineAI::init_(heap);
}

void KakarikoKokkoTimeline::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalTimelineAI::enter_(params);
}

void KakarikoKokkoTimeline::leave_() {
    AnimalTimelineAI::leave_();
}

void KakarikoKokkoTimeline::loadParams_() {
    AnimalTimelineAI::loadParams_();
    getStaticParam(&mForceChangeChildKeyName_s, "ForceChangeChildKeyName");
    getStaticParam(&mStartForceChangeFlagName_s, "StartForceChangeFlagName");
    getStaticParam(&mEndForceChangeFlagName_s, "EndForceChangeFlagName");
    getMapUnitParam(&mCheckGatheredFlagName_m, "CheckGatheredFlagName");
}

}  // namespace uking::ai
