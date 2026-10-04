#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPrizeSuccess : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPrizeSuccess, ksys::act::ai::Action)
public:
    explicit EventPrizeSuccess(const InitArg& arg);
    ~EventPrizeSuccess() override;

    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mPrizeNumber_d{};
};

}  // namespace uking::action
