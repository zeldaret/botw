#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantClosestAttackSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ForestGiantClosestAttackSelect, ksys::act::ai::Ai)
public:
    explicit ForestGiantClosestAttackSelect(const InitArg& arg);
    ~ForestGiantClosestAttackSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mHipDropRate_s{};
    // static_param at offset 0x40
    const int* mHipDropRateFar_s{};
    // static_param at offset 0x48
    const float* mFarDist_s{};
};

}  // namespace uking::ai
