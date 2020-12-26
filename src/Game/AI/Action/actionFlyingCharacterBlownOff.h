#pragma once

#include "Game/AI/Action/actionFlyingCharacterReaction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterBlownOff : public FlyingCharacterReaction {
    SEAD_RTTI_OVERRIDE(FlyingCharacterBlownOff, FlyingCharacterReaction)
public:
    explicit FlyingCharacterBlownOff(const InitArg& arg);
    ~FlyingCharacterBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mPosReduceRatioOnGround_s{};
    // static_param at offset 0x78
    const float* mRotReduceRatioOnGround_s{};
    // static_param at offset 0x80
    const float* mSpeed_s{};
    // static_param at offset 0x88
    const float* mRiseSpeed_s{};
    // static_param at offset 0x90
    sead::SafeString mFallAS_s{};
    // static_param at offset 0xa0
    sead::SafeString mOnGroundAS_s{};
};

}  // namespace uking::action
