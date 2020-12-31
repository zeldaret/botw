#include "Game/AI/AI/aiBokoblinNoise.h"

namespace uking::ai {

BokoblinNoise::BokoblinNoise(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BokoblinNoise::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BokoblinNoise::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BokoblinNoise::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BokoblinNoise::loadParams_() {
    getStaticParam(&mMaxContinueNum_s, "MaxContinueNum");
    getStaticParam(&mEnterNoiseRate_s, "EnterNoiseRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
