#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonBeastWeakPointCheck : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastWeakPointCheck, ksys::act::ai::Action)
public:
    explicit ForkGanonBeastWeakPointCheck(const InitArg& arg);
    ~ForkGanonBeastWeakPointCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mASSlot_s{};
    // static_param at offset 0x28
    const int* mLastWeakSlowEndSafeTime_s{};
    // static_param at offset 0x30
    const float* mLastWeakCounter_s{};
    // aitree_variable at offset 0x38
    int* mLastDamageWeakPointIdx_a{};
    // aitree_variable at offset 0x40
    bool* mIsWeakPointAppearMode_a{};
    // aitree_variable at offset 0x48
    void* mWeakPointActiveFlag_a{};
    // aitree_variable at offset 0x50
    void* mWeakPointAliveFlag_a{};
    // aitree_variable at offset 0x58
    void* mGanonBeastWeakPointXLinkHandle_a{};
    // aitree_variable at offset 0x60
    void* mWeakPointCounter_a{};
};

}  // namespace uking::action
