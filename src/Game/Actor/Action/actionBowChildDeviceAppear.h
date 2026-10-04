#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildDeviceAppear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildDeviceAppear, ksys::act::ai::Action)
public:
    explicit BowChildDeviceAppear(const InitArg& arg);
    ~BowChildDeviceAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitSpeed_s{};
    // static_param at offset 0x28
    const float* mEndTime_s{};
};

}  // namespace uking::action
