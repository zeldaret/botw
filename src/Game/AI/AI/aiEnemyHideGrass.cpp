#include "Game/AI/AI/aiEnemyHideGrass.h"

namespace uking::ai {

EnemyHideGrass::EnemyHideGrass(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHideGrass::~EnemyHideGrass() = default;

bool EnemyHideGrass::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyHideGrass::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyHideGrass::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHideGrass::loadParams_() {
    getStaticParam(&mSightRatio_s, "SightRatio");
    getStaticParam(&mHearingRatio_s, "HearingRatio");
}

}  // namespace uking::ai
