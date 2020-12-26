#pragma once

#include "Game/AI/Action/actionSwimMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimMoveASHoldEvent : public SwimMoveBase {
    SEAD_RTTI_OVERRIDE(SwimMoveASHoldEvent, SwimMoveBase)
public:
    explicit SwimMoveASHoldEvent(const InitArg& arg);
    ~SwimMoveASHoldEvent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    const float* mPosReduceRatio_s{};
    // static_param at offset 0xf0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
