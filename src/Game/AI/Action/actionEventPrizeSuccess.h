#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPrizeSuccess : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPrizeSuccess, ksys::act::ai::Action)
public:
    explicit EventPrizeSuccess(const InitArg& arg);
    ~EventPrizeSuccess() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mPrizeNumber_d{};
};

}  // namespace uking::action
