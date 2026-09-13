#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GoronCannonBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GoronCannonBase, ksys::act::ai::Ai)
public:
    explicit GoronCannonBase(const InitArg& arg);
    ~GoronCannonBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRotRadAccel_s{};
    // static_param at offset 0x40
    const float* mRotBrake_s{};
    // static_param at offset 0x48
    const float* mShotCannonBallScale_s{};
    // static_param at offset 0x50
    const bool* mIsDrawDebug_s{};
    // static_param at offset 0x58
    const bool* mIsUseShotNodeAngle_s{};
    // static_param at offset 0x60
    sead::SafeString mActName_s{};
    // static_param at offset 0x70
    sead::SafeString mShotNodeName_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mOffset_s{};
    // map_unit_param at offset 0x88
    const float* mTiltAngle_m{};
    // map_unit_param at offset 0x90
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x98
    const float* mAngle_m{};
    // map_unit_param at offset 0xa0
    const float* mSpeed_m{};
    // map_unit_param at offset 0xa8
    sead::SafeString mActorName_m{};
};

}  // namespace uking::ai
