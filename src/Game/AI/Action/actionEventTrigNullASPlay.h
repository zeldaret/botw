#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventTrigNullASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventTrigNullASPlay, ksys::act::ai::Action)
public:
    explicit EventTrigNullASPlay(const InitArg& arg);
    ~EventTrigNullASPlay() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mASSlot_d{};
    // dynamic_param at offset 0x28
    int* mSequenceBank_d{};
    // dynamic_param at offset 0x30
    bool* mIsIgnoreSame_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mASName_d{};
};

}  // namespace uking::action
