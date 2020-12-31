#pragma once

#include "Game/AI/AI/aiRailMoveRandomIgnoreStop.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveRndIgnrStopPlayAS : public RailMoveRandomIgnoreStop {
    SEAD_RTTI_OVERRIDE(RailMoveRndIgnrStopPlayAS, RailMoveRandomIgnoreStop)
public:
    explicit RailMoveRndIgnrStopPlayAS(const InitArg& arg);
    ~RailMoveRndIgnrStopPlayAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
