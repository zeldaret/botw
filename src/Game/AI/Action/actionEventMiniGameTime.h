#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventMiniGameTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventMiniGameTime, ksys::act::ai::Action)
public:
    explicit EventMiniGameTime(const InitArg& arg);
    ~EventMiniGameTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mCountMode_d{};
    // dynamic_param at offset 0x28
    int* mCountStartTime_d{};
    // dynamic_param at offset 0x30
    int* mMaxTime_d{};
    // dynamic_param at offset 0x38
    bool* mIsShowTimeUI_d{};
};

}  // namespace uking::action
