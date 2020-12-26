#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeginObservation : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeginObservation, ksys::act::ai::Action)
public:
    explicit BeginObservation(const InitArg& arg);
    ~BeginObservation() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    sead::SafeString mEventFlowName_m{};
    // map_unit_param at offset 0x30
    sead::SafeString mEventFlowEntryName_m{};
};

}  // namespace uking::action
