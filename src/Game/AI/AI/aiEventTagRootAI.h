#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EventTagRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EventTagRootAI, ksys::act::ai::Ai)
public:
    explicit EventTagRootAI(const InitArg& arg);
    ~EventTagRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x10];
    // map_unit_param at offset 0x48
    const bool* mLaunchEventByOnSignal_m{};
    // map_unit_param at offset 0x50
    const bool* mLaunchEventByOffSignal_m{};
    // map_unit_param at offset 0x58
    const bool* mIsEndlessEvent_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mEventFlowName_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mEventFlowEntryName_m{};
};

}  // namespace uking::ai
