#pragma once

#include "Game/AI/Action/actionPlayerGuidedMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerNavMeshMove : public PlayerGuidedMove {
    SEAD_RTTI_OVERRIDE(PlayerNavMeshMove, PlayerGuidedMove)
public:
    explicit PlayerNavMeshMove(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
