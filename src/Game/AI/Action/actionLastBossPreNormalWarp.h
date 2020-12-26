#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossPreNormalWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossPreNormalWarp, ksys::act::ai::Action)
public:
    explicit LastBossPreNormalWarp(const InitArg& arg);
    ~LastBossPreNormalWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPreWarpWaitTime_s{};
    // static_param at offset 0x28
    const float* mPosReduce_s{};
    // static_param at offset 0x30
    const bool* mIsDeleteEffect_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    bool* mIsPartsWarpEffectSync_d{};
};

}  // namespace uking::action
