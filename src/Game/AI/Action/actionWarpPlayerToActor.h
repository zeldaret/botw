#pragma once

#include "Game/AI/Action/actionWarpPlayerBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerToActor : public WarpPlayerBase {
    SEAD_RTTI_OVERRIDE(WarpPlayerToActor, WarpPlayerBase)
public:
    explicit WarpPlayerToActor(const InitArg& arg);
    ~WarpPlayerToActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x60
    float* mDestinationX_d{};
    // dynamic_param at offset 0x68
    float* mDestinationY_d{};
    // dynamic_param at offset 0x70
    float* mDestinationZ_d{};
    // dynamic_param at offset 0x78
    float* mDirectionY_d{};
    // dynamic_param at offset 0x80
    float* mRelativeDist_d{};
    // dynamic_param at offset 0x88
    bool* mRotToVec3f_d{};
    // dynamic_param at offset 0x90
    bool* mOnGround_d{};
    // dynamic_param at offset 0x98
    bool* mIsOffsetBaseTargetActor_d{};
    // dynamic_param at offset 0xa0
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0xb0
    sead::SafeString mGameDataVec3fRotDir_d{};
};

}  // namespace uking::action
