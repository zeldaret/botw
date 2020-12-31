#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelChaseBattleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelChaseBattleMove, ksys::act::ai::Ai)
public:
    explicit LynelChaseBattleMove(const InitArg& arg);
    ~LynelChaseBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSlowDownDist_s{};
    // static_param at offset 0x40
    const float* mSpeedUpDist_s{};
    // static_param at offset 0x48
    const float* mBaseDist_s{};
    // static_param at offset 0x50
    const float* mOutDist_s{};
    // static_param at offset 0x58
    const float* mCloseStartDist_s{};
};

}  // namespace uking::ai
