#include "Game/AI/AI/aiPriestBossActorGiantFouthRoot.h"

namespace uking::ai {

PriestBossActorGiantFouthRoot::PriestBossActorGiantFouthRoot(const InitArg& arg)
    : PriestBossActorGiantRoot(arg) {}

PriestBossActorGiantFouthRoot::~PriestBossActorGiantFouthRoot() = default;

bool PriestBossActorGiantFouthRoot::init_(sead::Heap* heap) {
    return PriestBossActorGiantRoot::init_(heap);
}

void PriestBossActorGiantFouthRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossActorGiantRoot::enter_(params);
}

void PriestBossActorGiantFouthRoot::leave_() {
    PriestBossActorGiantRoot::leave_();
}

void PriestBossActorGiantFouthRoot::loadParams_() {
    PriestBossActorGiantRoot::loadParams_();
    getStaticParam(&mStompDistance_s, "StompDistance");
    getStaticParam(&mStompInAreaTimer_s, "StompInAreaTimer");
    getStaticParam(&mStompAction_s, "StompAction");
    getStaticParam(&mStompAlwaysChange_s, "StompAlwaysChange");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
