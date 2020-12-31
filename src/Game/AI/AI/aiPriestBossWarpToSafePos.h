#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossWarpToSafePos : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossWarpToSafePos, PriestBossMode)
public:
    explicit PriestBossWarpToSafePos(const InitArg& arg);
    ~PriestBossWarpToSafePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mOffsetY_s{};
    // static_param at offset 0x48
    const float* mOffsetZ_s{};
    // aitree_variable at offset 0x50
    bool* mIsActive_a{};
    // aitree_variable at offset 0x58
    sead::Vector3f* mDestinationPos_a{};
};

}  // namespace uking::ai
