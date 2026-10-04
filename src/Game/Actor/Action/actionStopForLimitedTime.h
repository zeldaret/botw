#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopForLimitedTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StopForLimitedTime, ksys::act::ai::Action)
public:
    explicit StopForLimitedTime(const InitArg& arg);
    ~StopForLimitedTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mKeepActRotation_s{};
    // static_param at offset 0x28
    const bool* mEnableStaticCompoundRotate_s{};
    // static_param at offset 0x30
    const bool* mIsSetEndByTime_s{};
    // static_param at offset 0x38
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x48
    float* mDynStopTime_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mDynStopPos_d{};
};

}  // namespace uking::action
