#include "Game/AI/AI/aiPriestBossMeta.h"

namespace uking::ai {

PriestBossMeta::PriestBossMeta(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMeta::~PriestBossMeta() = default;

bool PriestBossMeta::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMeta::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossMeta::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossMeta::loadParams_() {
    getAITreeVariable(&mMetaAILife_a, "MetaAILife");
    getAITreeVariable(&mMetaAIMaxLife_a, "MetaAIMaxLife");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
