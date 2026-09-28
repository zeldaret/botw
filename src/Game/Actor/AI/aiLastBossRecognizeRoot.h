#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossRecognizeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossRecognizeRoot, ksys::act::ai::Ai)
public:
    explicit LastBossRecognizeRoot(const InitArg& arg);
    ~LastBossRecognizeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackNum_s{};
    // static_param at offset 0x40
    const int* mAttackRandNum_s{};
    // static_param at offset 0x48
    const float* mWarpStartDist_s{};
    // static_param at offset 0x50
    const float* mForceWarpRetryDist_s{};
    // dynamic_param at offset 0x58
    bool* mIsAttackPatternFixed_d{};
};

}  // namespace uking::ai
