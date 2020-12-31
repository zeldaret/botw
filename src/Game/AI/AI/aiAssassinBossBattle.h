#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinBossBattle, ksys::act::ai::Ai)
public:
    explicit AssassinBossBattle(const InitArg& arg);
    ~AssassinBossBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRetFrmDmgAtkTimer_s{};
    // static_param at offset 0x40
    const float* mIntervalIntensity_s{};
    // static_param at offset 0x48
    const float* mHomeDist_s{};
    // static_param at offset 0x50
    const float* mBattleDist_s{};
    // static_param at offset 0x58
    const float* mDyingLifeRatio_s{};
    // static_param at offset 0x60
    const float* mBattleDistSecond_s{};
    // static_param at offset 0x68
    const float* mReturnHeight_s{};
    // static_param at offset 0x70
    sead::SafeString mAnchorName_s{};
};

}  // namespace uking::ai
