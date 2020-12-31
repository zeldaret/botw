#pragma once

#include "Game/AI/AI/aiRailMoveWithClose.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveRandomIgnoreStop : public RailMoveWithClose {
    SEAD_RTTI_OVERRIDE(RailMoveRandomIgnoreStop, RailMoveWithClose)
public:
    explicit RailMoveRandomIgnoreStop(const InitArg& arg);
    ~RailMoveRandomIgnoreStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb8
    const int* mStopRate_s{};
};

}  // namespace uking::ai
