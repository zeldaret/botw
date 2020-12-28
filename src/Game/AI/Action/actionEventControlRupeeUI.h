#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventControlRupeeUI : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventControlRupeeUI, ksys::act::ai::Action)
public:
    explicit EventControlRupeeUI(const InitArg& arg);
    ~EventControlRupeeUI() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mTargetValue_d{};
    // dynamic_param at offset 0x28
    bool* mIsAppear_d{};
};

}  // namespace uking::action
