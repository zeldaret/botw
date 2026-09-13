#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyLook : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LevelFlyLook, ksys::act::ai::Action)
public:
    explicit LevelFlyLook(const InitArg& arg);
    ~LevelFlyLook() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mHeight_s{};
    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpeed_s{};
    // static_param at offset 0x38
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x40
    const float* mRotRatio_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
