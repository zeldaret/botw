#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopEventMiniGameTime : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StopEventMiniGameTime, ksys::act::ai::Action)
public:
    explicit StopEventMiniGameTime(const InitArg& arg);
    ~StopEventMiniGameTime() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
