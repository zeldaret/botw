#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CloseClockTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CloseClockTime, ksys::act::ai::Action)
public:
    explicit CloseClockTime(const InitArg& arg);
    ~CloseClockTime() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
