#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventFade : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventFade, ksys::act::ai::Action)
public:
    explicit EventFade(const InitArg& arg);
    ~EventFade() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mFrame_d{};
    // dynamic_param at offset 0x28
    int* mColor_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mDispMode_d{};
};

}  // namespace uking::action
