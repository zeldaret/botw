#pragma once

#include "Game/AI/AI/aiRandomSelectThreeActionBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RandomSelectThreeAction : public RandomSelectThreeActionBase {
    SEAD_RTTI_OVERRIDE(RandomSelectThreeAction, RandomSelectThreeActionBase)
public:
    explicit RandomSelectThreeAction(const InitArg& arg);
    ~RandomSelectThreeAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const float* mRateActionA_s{};
    // static_param at offset 0x68
    const float* mRateActionB_s{};
    // static_param at offset 0x70
    const float* mRateActionC_s{};
};

}  // namespace uking::ai
