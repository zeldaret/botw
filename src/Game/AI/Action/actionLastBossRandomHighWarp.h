#pragma once

#include "Game/AI/Action/actionLastBossNormalWarp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossRandomHighWarp : public LastBossNormalWarp {
    SEAD_RTTI_OVERRIDE(LastBossRandomHighWarp, LastBossNormalWarp)
public:
    explicit LastBossRandomHighWarp(const InitArg& arg);
    ~LastBossRandomHighWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xf8
    const int* mHighPosWarpRate_s{};
    // static_param at offset 0x100
    const int* mRandomRate_s{};
    // static_param at offset 0x108
    const float* mHighOffsetY_s{};
    // static_param at offset 0x110
    const float* mLifeCondition_s{};
};

}  // namespace uking::action
