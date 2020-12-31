#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossNormalWarpRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastBossNormalWarpRoot, ksys::act::ai::Ai)
public:
    explicit LastBossNormalWarpRoot(const InitArg& arg);
    ~LastBossNormalWarpRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsKeepDisableDraw_s{};
    // static_param at offset 0x40
    sead::SafeString mSleepPartsActorName_s{};
    // dynamic_param at offset 0x50
    bool* mIsReturnHome_d{};
    // dynamic_param at offset 0x58
    bool* mIsForceWarp_d{};
    // dynamic_param at offset 0x60
    bool* mIsPartsActorTgOn_d{};
    // dynamic_param at offset 0x68
    bool* mIsPartsWarpEffectSync_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
