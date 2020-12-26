#pragma once

#include "Game/AI/Action/actionWaterFloatImmobile.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatWait : public WaterFloatImmobile {
    SEAD_RTTI_OVERRIDE(WaterFloatWait, WaterFloatImmobile)
public:
    explicit WaterFloatWait(const InitArg& arg);
    ~WaterFloatWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const int* mTime_s{};
    // static_param at offset 0x78
    const int* mTimeRand_s{};
    // static_param at offset 0x80
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x88
    const bool* mIsEndWhenASFinished_s{};
    // static_param at offset 0x90
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
