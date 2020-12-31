#include "Game/AI/AI/aiLastBossWeaponAttackRoot.h"

namespace uking::ai {

LastBossWeaponAttackRoot::LastBossWeaponAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossWeaponAttackRoot::~LastBossWeaponAttackRoot() = default;

bool LastBossWeaponAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossWeaponAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossWeaponAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossWeaponAttackRoot::loadParams_() {
    getStaticParam(&mEnemyType_s, "EnemyType");
    getStaticParam(&mIsStartBossBgm_s, "IsStartBossBgm");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mReappearanceDist_s, "ReappearanceDist");
    getStaticParam(&mReappearanceDistOffset_s, "ReappearanceDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

}  // namespace uking::ai
