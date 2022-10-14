#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KorokTargetWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(KorokTargetWait, ksys::act::ai::Action)
public:
    explicit KorokTargetWait(const InitArg& arg);
    ~KorokTargetWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeedDecreRate_s{};
    // dynamic_param at offset 0x28
    float* mDynStopTime_d{};

    f32 mTime;
};

}  // namespace uking::action
