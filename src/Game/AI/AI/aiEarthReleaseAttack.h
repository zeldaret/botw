#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EarthReleaseAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EarthReleaseAttack, ksys::act::ai::Ai)
public:
    explicit EarthReleaseAttack(const InitArg& arg);
    ~EarthReleaseAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackPower_s{};
    // static_param at offset 0x40
    const float* mEnlargeTime_s{};
    // static_param at offset 0x48
    const float* mRange_s{};
    // static_param at offset 0x50
    const float* mScale_s{};
    // static_param at offset 0x58
    const bool* mUseAfterAction_s{};
    // static_param at offset 0x60
    sead::SafeString mEarthReleaseActorName_s{};
    // static_param at offset 0x70
    sead::SafeString mEarthReleasePartsName_s{};
};

}  // namespace uking::ai
