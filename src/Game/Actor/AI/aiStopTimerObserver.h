#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StopTimerObserver : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StopTimerObserver, ksys::act::ai::Ai)
public:
    explicit StopTimerObserver(const InitArg& arg);
    ~StopTimerObserver() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
