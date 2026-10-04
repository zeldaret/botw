#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaitForFrame : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaitForFrame, ksys::act::ai::Action)
public:
    explicit WaitForFrame(const InitArg& arg);
    ~WaitForFrame() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mValidInput_s{};
    // dynamic_param at offset 0x28
    int* mFrame_d{};
};

}  // namespace uking::action
