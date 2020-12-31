#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRangeKeepMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRangeKeepMove, ksys::act::ai::Ai)
public:
    explicit AnimalRangeKeepMove(const InitArg& arg);
    ~AnimalRangeKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mBattleEndTimerMin_s{};
    // static_param at offset 0x40
    const int* mBattleEndTimerMax_s{};
    // static_param at offset 0x48
    const float* mCloseStartDist_s{};
    // static_param at offset 0x50
    const float* mCloseEndDist_s{};
    // static_param at offset 0x58
    const float* mLeaveStartDist_s{};
    // static_param at offset 0x60
    const float* mLeaveEndDist_s{};
    // static_param at offset 0x68
    const float* mBattleEndDist_s{};
};

}  // namespace uking::ai
