#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Warn : public StopASPlay {
    SEAD_RTTI_OVERRIDE(Warn, StopASPlay)
public:
    explicit Warn(const InitArg& arg);
    ~Warn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
