#include "Game/AI/AI/aiDomesticNormal.h"

namespace uking::ai {

DomesticNormal::DomesticNormal(const InitArg& arg) : PreyNormal(arg) {}

DomesticNormal::~DomesticNormal() = default;

bool DomesticNormal::init_(sead::Heap* heap) {
    return PreyNormal::init_(heap);
}

void DomesticNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyNormal::enter_(params);
}

void DomesticNormal::leave_() {
    PreyNormal::leave_();
}

void DomesticNormal::loadParams_() {
    PreyNormal::loadParams_();
    getStaticParam(&mWaitFramesAfterRunMax_s, "WaitFramesAfterRunMax");
    getStaticParam(&mNumFailPathHomeFadeout_s, "NumFailPathHomeFadeout");
    getStaticParam(&mDistUntilReturnToHomePos_s, "DistUntilReturnToHomePos");
    getStaticParam(&mWaitFramesAfterRunMin_s, "WaitFramesAfterRunMin");
    getStaticParam(&mStaggerVelocityThreshold_s, "StaggerVelocityThreshold");
    getStaticParam(&mDistHomePosFadeout_s, "DistHomePosFadeout");
    getAITreeVariable(&mDomesticAnimalRailName_a, "DomesticAnimalRailName");
}

}  // namespace uking::ai
