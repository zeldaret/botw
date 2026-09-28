#include "Game/Actor/AI/aiAwnSeal.h"

namespace uking::ai {

AwnSeal::AwnSeal(const InitArg& arg) : EnemyNormal(arg) {}

AwnSeal::~AwnSeal() = default;

bool AwnSeal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void AwnSeal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void AwnSeal::leave_() {
    EnemyNormal::leave_();
}

void AwnSeal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mSealedSight_s, "SealedSight");
    getStaticParam(&mSealedHearing_s, "SealedHearing");
    getStaticParam(&mSealedTerror_s, "SealedTerror");
    getStaticParam(&mSealedWorry_s, "SealedWorry");
}

}  // namespace uking::ai
