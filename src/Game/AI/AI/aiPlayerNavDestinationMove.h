#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerNavDestinationMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerNavDestinationMove, ksys::act::ai::Ai)
public:
    explicit PlayerNavDestinationMove(const InitArg& arg);
    ~PlayerNavDestinationMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    float* mDestPosX_d{};
    // dynamic_param at offset 0x40
    float* mDestPosY_d{};
    // dynamic_param at offset 0x48
    float* mDestPosZ_d{};
    // dynamic_param at offset 0x50
    float* mStickValue_d{};
};

}  // namespace uking::ai
