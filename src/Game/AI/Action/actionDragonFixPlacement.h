#pragma once

#include "Game/AI/Action/actionNullASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonFixPlacement : public NullASPlay {
    SEAD_RTTI_OVERRIDE(DragonFixPlacement, NullASPlay)
public:
    explicit DragonFixPlacement(const InitArg& arg);
    ~DragonFixPlacement() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const int* mBlendStartFrame_s{};
    // static_param at offset 0x50
    const int* mHeadFixedModeTime_s{};
    // static_param at offset 0x58
    const int* mRailAdjustModeTime_s{};
    // static_param at offset 0x60
    const int* mCameraVibStartFrame_s{};
    // static_param at offset 0x68
    const int* mCameraVibLoop_s{};
    // static_param at offset 0x70
    const float* mBlendStartRate_s{};
    // static_param at offset 0x78
    const float* mBlendTime_s{};
    // static_param at offset 0x80
    const float* mCameraVibPower_s{};
    // static_param at offset 0x88
    const float* mCameraVibRange_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mRotate_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mPosition_s{};
};

}  // namespace uking::action
