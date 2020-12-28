#pragma once

#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniBeamMove : public BeamMove {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamMove, BeamMove)
public:
    explicit GuardianMiniBeamMove(const InitArg& arg);
    ~GuardianMiniBeamMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mReboundDeccel_s{};
};

}  // namespace uking::action
