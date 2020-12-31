#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossGiantDownSeq : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossGiantDownSeq, PriestBossMode)
public:
    explicit PriestBossGiantDownSeq(const InitArg& arg);
    ~PriestBossGiantDownSeq() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const bool* mRecoverIfAlreadyDown_s{};
    // static_param at offset 0x48
    const bool* mIsUseRecover_s{};
    // static_param at offset 0x50
    sead::SafeString mHitGroundASName_s{};
    // aitree_variable at offset 0x60
    float* mKeepDistFromGround_a{};
    // aitree_variable at offset 0x68
    bool* mIsActive_a{};
    // aitree_variable at offset 0x70
    bool* mIsArrivedAtDestination_a{};
    // aitree_variable at offset 0x78
    sead::Vector3f* mDestinationPos_a{};
};

}  // namespace uking::ai
