#pragma once

#include "Game/AI/Action/actionGuardianBeamFire.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniFinalBeamMove : public GuardianBeamFire {
    SEAD_RTTI_OVERRIDE(GuardianMiniFinalBeamMove, GuardianBeamFire)
public:
    explicit GuardianMiniFinalBeamMove(const InitArg& arg);
    ~GuardianMiniFinalBeamMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
