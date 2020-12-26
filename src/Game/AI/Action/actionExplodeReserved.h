#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ExplodeReserved : public StopASPlay {
    SEAD_RTTI_OVERRIDE(ExplodeReserved, StopASPlay)
public:
    explicit ExplodeReserved(const InitArg& arg);
    ~ExplodeReserved() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
