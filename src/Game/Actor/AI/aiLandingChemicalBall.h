#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandingChemicalBall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LandingChemicalBall, ksys::act::ai::Ai)
public:
    explicit LandingChemicalBall(const InitArg& arg);
    ~LandingChemicalBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackPower_s{};
    // static_param at offset 0x40
    const int* mAttackIntensity_s{};
    // static_param at offset 0x48
    const int* mAttackType_s{};
    // static_param at offset 0x50
    const int* mCutGrassType_s{};
    // static_param at offset 0x58
    const float* mScale_s{};
    // static_param at offset 0x60
    const bool* mIsUseAtCollision_s{};
    // static_param at offset 0x68
    const bool* mCheckColConInfo_s{};
    // static_param at offset 0x70
    sead::SafeString mExpandActorName_s{};
};

}  // namespace uking::ai
