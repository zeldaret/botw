#pragma once

#include "Game/AI/AI/aiCircleMoveInFluid.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CircleMoveFlying : public CircleMoveInFluid {
    SEAD_RTTI_OVERRIDE(CircleMoveFlying, CircleMoveInFluid)
public:
    explicit CircleMoveFlying(const InitArg& arg);
    ~CircleMoveFlying() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const bool* mIsCheckSafetyAreaRadius_s{};
    // static_param at offset 0xe8
    const bool* mIsUseHomePos_s{};
};

}  // namespace uking::ai
