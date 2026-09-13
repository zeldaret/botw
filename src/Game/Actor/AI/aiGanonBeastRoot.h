#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastRoot, ksys::act::ai::Ai)
public:
    explicit GanonBeastRoot(const InitArg& arg);
    ~GanonBeastRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsGanonBeastAngry_a{};
    // aitree_variable at offset 0x40
    void* mWeakPointAliveFlag_a{};
    // aitree_variable at offset 0x48
    void* mWeakPointActiveFlag_a{};
    // static_param at offset 0x90
    sead::SafeString mGrudeRainObject_s{};
    // static_param at offset 0xa0
    sead::SafeString mGrudeRainObject2_s{};
    // static_param at offset 0xc0
    const int* mGrudeInterval3_s{};
    // static_param at offset 0xc8
    const int* mGrudeInterval4_s{};
    // static_param at offset 0xd0
    const int* mGrudeInterval5_s{};
    // static_param at offset 0xd8
    const int* mGrudeCreateNum_s{};
    // static_param at offset 0xe0
    const int* mWeakPointASSlot_s{};
    // static_param at offset 0xe8
    const float* mGrudePlayerDist_s{};
    // static_param at offset 0xf0
    const float* mGrudeRandRange_s{};
    // static_param at offset 0xf8
    const float* mGrudeCenterOffset_s{};
    // static_param at offset 0x100
    sead::SafeString mInitWeakPointASName_s{};
};

}  // namespace uking::ai
