#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TreasureBoxRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TreasureBoxRoot, ksys::act::ai::Ai)
public:
    explicit TreasureBoxRoot(const InitArg& arg);
    ~TreasureBoxRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mInGroundOffsetY_s{};
    // static_param at offset 0x40
    const float* mInGroundScale_s{};
    // static_param at offset 0x48
    const float* mOnGroundOffsetY_s{};
    // static_param at offset 0x50
    const float* mOnGroundScale_s{};
    // static_param at offset 0x58
    const float* mJumpPower_s{};
    // static_param at offset 0x60
    const bool* mDebugDraw_s{};
    // map_unit_param at offset 0x68
    const bool* mIsInGround_m{};
    // map_unit_param at offset 0x70
    const bool* mEnableRevival_m{};
};

}  // namespace uking::ai
