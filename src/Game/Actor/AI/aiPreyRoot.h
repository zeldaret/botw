#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyRoot, ksys::act::ai::Ai)
public:
    explicit PreyRoot(const InitArg& arg);
    ~PreyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAfterEscapeForceEndState_s{};
    // static_param at offset 0x40
    const float* mInWaterDepth_s{};
    // static_param at offset 0x48
    const float* mEscapeForceEndTime_s{};
    // static_param at offset 0x50
    const bool* mIsCheckFreeFall_s{};
    // static_param at offset 0x58
    const bool* mIsCheckStuckConsiderY_s{};
    // static_param at offset 0x60
    const bool* mIsUseWeakForcePushOutside_s{};
    // static_param at offset 0x68
    const bool* mIsEnableEscapeForceEndCheck_s{};
    // aitree_variable at offset 0x70
    int* mCreateDeadConditionType_a{};
    // aitree_variable at offset 0x78
    float* mFramesStuckOnTerrain_a{};
    // aitree_variable at offset 0x80
    bool* mIsStuckOnTerrain_a{};
    // aitree_variable at offset 0x88
    bool* mIsChangeableStateFreeFall_a{};
    // aitree_variable at offset 0x90
    bool* mIsUseTerritory_a{};
};

}  // namespace uking::ai
