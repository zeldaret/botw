#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTag4WaterApp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTag4WaterApp, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTag4WaterApp(const InitArg& arg);
    ~DungeonRotateTag4WaterApp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLv0_s{};
    // static_param at offset 0x40
    const float* mLv1_s{};
    // static_param at offset 0x48
    const float* mLv2_s{};
    // static_param at offset 0x50
    const float* mLv3_s{};
    // static_param at offset 0x58
    const float* mLv4_s{};
    // static_param at offset 0x60
    const float* mLv5_s{};
    // static_param at offset 0x68
    const float* mLv6_s{};
    // static_param at offset 0x70
    const float* mLv7_s{};
    // static_param at offset 0x78
    const float* mLv8_s{};
    // static_param at offset 0x80
    const float* mLv9_s{};
    // aitree_variable at offset 0x88
    float* mTargetRad_a{};
    // aitree_variable at offset 0x90
    float* mTargetRadMax_a{};
    // aitree_variable at offset 0x98
    float* mTargetRadMin_a{};
};

}  // namespace uking::ai
