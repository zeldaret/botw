#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossBowHoldTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(SiteBossBowHoldTurn, TurnBase)
public:
    explicit SiteBossBowHoldTurn(const InitArg& arg);
    ~SiteBossBowHoldTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const float* mSpineControlOffsetAngleLR_s{};
    // static_param at offset 0x98
    const float* mSpineControlOffsetAngleUD_s{};
    // static_param at offset 0xa0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
