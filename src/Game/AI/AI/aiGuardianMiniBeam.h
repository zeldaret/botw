#pragma once

#include "Game/AI/AI/aiBeamExplodeBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeam : public BeamExplodeBase {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeam, BeamExplodeBase)
public:
    explicit GuardianMiniBeam(const InitArg& arg);
    ~GuardianMiniBeam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
