#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTebaApproachPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCTebaApproachPlayer, ksys::act::ai::Action)
public:
    explicit NPCTebaApproachPlayer(const InitArg& arg);
    ~NPCTebaApproachPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mUpdateTargetFrame_s{};
    // static_param at offset 0x28
    const float* mPlayerMaxHeight_s{};
    // static_param at offset 0x30
    const float* mMaxMoveSpeed_s{};
    // static_param at offset 0x38
    const float* mTurnSpeed_s{};
    // static_param at offset 0x40
    const float* mTurnRadius_s{};
    // static_param at offset 0x48
    const float* mReduceMaxSpeedChasePlayer_s{};
};

}  // namespace uking::action
