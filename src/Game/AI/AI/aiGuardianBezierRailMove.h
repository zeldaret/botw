#pragma once

#include "Game/AI/AI/aiRailMoveWithClose.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianBezierRailMove : public RailMoveWithClose {
    SEAD_RTTI_OVERRIDE(GuardianBezierRailMove, RailMoveWithClose)
public:
    explicit GuardianBezierRailMove(const InitArg& arg);
    ~GuardianBezierRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
