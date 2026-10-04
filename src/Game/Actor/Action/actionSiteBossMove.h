#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossMove, ksys::act::ai::Action)
public:
    explicit SiteBossMove(const InitArg& arg);
    ~SiteBossMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mAccRatio_s{};
    // static_param at offset 0x30
    const float* mUpdownSpeed_s{};
    // static_param at offset 0x38
    const float* mAmplitude_s{};
    // static_param at offset 0x40
    const float* mRotateRate_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mMoveDstPos_d{};
};

}  // namespace uking::action
