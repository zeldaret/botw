#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RequestEventFromMapUnit : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RequestEventFromMapUnit, ksys::act::ai::Action)
public:
    explicit RequestEventFromMapUnit(const InitArg& arg);
    ~RequestEventFromMapUnit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsWaitStartEvent_s{};
    // static_param at offset 0x28
    sead::SafeString mASKey_s{};
    // map_unit_param at offset 0x38
    sead::SafeString mEventFlowName_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mEventFlowEntryName_m{};
};

}  // namespace uking::action
