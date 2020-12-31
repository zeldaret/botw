#pragma once

#include "Game/AI/AI/aiBeamExplodeBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeamExplode : public BeamExplodeBase {
    SEAD_RTTI_OVERRIDE(BeamExplode, BeamExplodeBase)
public:
    explicit BeamExplode(const InitArg& arg);
    ~BeamExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
