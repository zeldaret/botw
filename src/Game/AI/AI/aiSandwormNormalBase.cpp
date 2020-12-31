#include "Game/AI/AI/aiSandwormNormalBase.h"

namespace uking::ai {

SandwormNormalBase::SandwormNormalBase(const InitArg& arg) : EnemyNormal(arg) {}

SandwormNormalBase::~SandwormNormalBase() = default;

bool SandwormNormalBase::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void SandwormNormalBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void SandwormNormalBase::leave_() {
    EnemyNormal::leave_();
}

void SandwormNormalBase::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSealedSight_s, "SealedSight");
    getStaticParam(&mSealedHearing_s, "SealedHearing");
    getStaticParam(&mSealedTerror_s, "SealedTerror");
    getStaticParam(&mSealedWorry_s, "SealedWorry");
}

}  // namespace uking::ai
