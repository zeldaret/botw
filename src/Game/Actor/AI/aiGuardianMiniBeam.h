#pragma once

#include "Game/Actor/AI/aiSimpleBeamExplode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeam : public SimpleBeamExplode {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeam, SimpleBeamExplode)
public:
    explicit GuardianMiniBeam(const InitArg& arg);
    ~GuardianMiniBeam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
