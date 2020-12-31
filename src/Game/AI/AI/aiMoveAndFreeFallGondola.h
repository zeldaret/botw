#pragma once

#include "Game/AI/AI/aiRailMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoveAndFreeFallGondola : public RailMove {
    SEAD_RTTI_OVERRIDE(MoveAndFreeFallGondola, RailMove)
public:
    explicit MoveAndFreeFallGondola(const InitArg& arg);
    ~MoveAndFreeFallGondola() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0xa0
    const float* mRailMoveSpeed_m{};
    // map_unit_param at offset 0xa8
    const float* mGondolaRailOffsetTime_m{};
};

}  // namespace uking::ai
