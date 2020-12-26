#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OneTimeStopASPlayerNoEnd : public StopASPlay {
    SEAD_RTTI_OVERRIDE(OneTimeStopASPlayerNoEnd, StopASPlay)
public:
    explicit OneTimeStopASPlayerNoEnd(const InitArg& arg);
    ~OneTimeStopASPlayerNoEnd() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
