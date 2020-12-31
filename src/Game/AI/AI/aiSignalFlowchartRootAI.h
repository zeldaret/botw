#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SignalFlowchartRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SignalFlowchartRootAI, ksys::act::ai::Ai)
public:
    explicit SignalFlowchartRootAI(const InitArg& arg);
    ~SignalFlowchartRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    sead::SafeString mEventFlowName_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mEventFlowEntryName_m{};
};

}  // namespace uking::ai
