#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAppearRaceResult : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAppearRaceResult, ksys::act::ai::Action)
public:
    explicit EventAppearRaceResult(const InitArg& arg);
    ~EventAppearRaceResult() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mResultType_d{};
};

}  // namespace uking::action
