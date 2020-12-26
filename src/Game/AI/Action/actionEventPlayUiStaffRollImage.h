#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPlayUiStaffRollImage : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayUiStaffRollImage, ksys::act::ai::Action)
public:
    explicit EventPlayUiStaffRollImage(const InitArg& arg);
    ~EventPlayUiStaffRollImage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mClipIndex_d{};
    // dynamic_param at offset 0x28
    int* mStartIdx_d{};
    // dynamic_param at offset 0x30
    int* mEndIdx_d{};
};

}  // namespace uking::action
