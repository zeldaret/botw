#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossWeaponAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossWeaponAttackRoot, ksys::act::ai::Ai)
public:
    explicit LastBossWeaponAttackRoot(const InitArg& arg);
    ~LastBossWeaponAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mEnemyType_s{};
    // static_param at offset 0x40
    const bool* mIsStartBossBgm_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mChaseDist_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mChaseDistOffset_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mReappearanceDist_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mReappearanceDistOffset_s{};
    // dynamic_param at offset 0x68
    bool* mIsAttackPatternFixed_d{};
};

}  // namespace uking::ai
