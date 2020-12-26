#pragma once

#include "Game/AI/Action/actionLevelFlyMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WizzrobeVisibleWalk : public LevelFlyMove {
    SEAD_RTTI_OVERRIDE(WizzrobeVisibleWalk, LevelFlyMove)
public:
    explicit WizzrobeVisibleWalk(const InitArg& arg);
    ~WizzrobeVisibleWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x148
    const float* mAddTargetDist_s{};
    // static_param at offset 0x150
    const float* mFailMoveTimer_s{};
    // static_param at offset 0x158
    const bool* mIsCheckAnmSeqCancel_s{};
    // static_param at offset 0x160
    const bool* mIsNoBrake_s{};
};

}  // namespace uking::action
