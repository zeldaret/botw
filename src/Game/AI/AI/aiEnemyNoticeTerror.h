#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeTerror : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNoticeTerror, ksys::act::ai::Ai)
public:
    explicit EnemyNoticeTerror(const InitArg& arg);
    ~EnemyNoticeTerror() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWaitTime_s{};
    // static_param at offset 0x40
    const float* mNoWarnDist_s{};
    // static_param at offset 0x48
    const float* mNoWarnHeightMin_s{};
    // static_param at offset 0x50
    const float* mNoWarnHeightMax_s{};
    // static_param at offset 0x58
    const float* mNoTerrorDist_s{};
};

}  // namespace uking::ai
