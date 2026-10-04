#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPickOutFromPorch : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPickOutFromPorch, ksys::act::ai::Action)
public:
    explicit EventPickOutFromPorch(const InitArg& arg);
    ~EventPickOutFromPorch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mPickOutItemType_s{};
    // dynamic_param at offset 0x28
    bool* mIsUseCarryBox_d{};
};

}  // namespace uking::action
