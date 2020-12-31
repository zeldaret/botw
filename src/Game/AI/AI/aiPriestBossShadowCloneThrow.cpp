#include "Game/AI/AI/aiPriestBossShadowCloneThrow.h"

namespace uking::ai {

PriestBossShadowCloneThrow::PriestBossShadowCloneThrow(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

PriestBossShadowCloneThrow::~PriestBossShadowCloneThrow() = default;

bool PriestBossShadowCloneThrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossShadowCloneThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossShadowCloneThrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossShadowCloneThrow::loadParams_() {
    getStaticParam(&mShadowCloneOffsetY_s, "ShadowCloneOffsetY");
    getStaticParam(&mShadowCloneRadius_s, "ShadowCloneRadius");
    getStaticParam(&mShadowCloneAngleOffset_s, "ShadowCloneAngleOffset");
    getStaticParam(&mPrepareTimer_s, "PrepareTimer");
    getStaticParam(&mShadowCloneLefeBoneName_s, "ShadowCloneLefeBoneName");
    getStaticParam(&mShadowCloneRightBoneName_s, "ShadowCloneRightBoneName");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
