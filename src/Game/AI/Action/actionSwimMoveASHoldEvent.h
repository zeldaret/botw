#pragma once

#include "Game/AI/Action/actionSwimMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimMoveASHoldEvent : public SwimMoveBase {
    SEAD_RTTI_OVERRIDE(SwimMoveASHoldEvent, SwimMoveBase)
public:
    explicit SwimMoveASHoldEvent(const InitArg& arg);
    ~SwimMoveASHoldEvent() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe8
    const float* mPosReduceRatio_s{};
    // static_param at offset 0xf0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
