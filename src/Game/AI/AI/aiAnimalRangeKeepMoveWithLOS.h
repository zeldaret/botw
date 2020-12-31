#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRangeKeepMoveWithLOS : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRangeKeepMoveWithLOS, ksys::act::ai::Ai)
public:
    explicit AnimalRangeKeepMoveWithLOS(const InitArg& arg);
    ~AnimalRangeKeepMoveWithLOS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFindPathBeginTimer_s{};
    // static_param at offset 0x40
    const int* mNoPathTimer_s{};
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
    // static_param at offset 0x70
    const float* mDistFailOnUnreachablePath_s{};
};

}  // namespace uking::ai
