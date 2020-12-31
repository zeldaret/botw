#pragma once

#include "Game/AI/AI/aiGanonBeastWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastDying : public GanonBeastWait {
    SEAD_RTTI_OVERRIDE(GanonBeastDying, GanonBeastWait)
public:
    explicit GanonBeastDying(const InitArg& arg);
    ~GanonBeastDying() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
