#pragma once

#include "Game/Actor/AI/aiBezierRailMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveWithClose : public BezierRailMove {
    SEAD_RTTI_OVERRIDE(RailMoveWithClose, BezierRailMove)
public:
    explicit RailMoveWithClose(const InitArg& arg);
    ~RailMoveWithClose() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa0
    const float* mOnRailDistance_s{};
    // static_param at offset 0xa8
    const float* mFarDistance_s{};
    // static_param at offset 0xb0
    const float* mSpeed_s{};
};

}  // namespace uking::ai
