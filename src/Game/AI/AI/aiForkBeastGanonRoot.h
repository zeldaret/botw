#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForkBeastGanonRoot : public ForkAI {
    SEAD_RTTI_OVERRIDE(ForkBeastGanonRoot, ForkAI)
public:
    explicit ForkBeastGanonRoot(const InitArg& arg);
    ~ForkBeastGanonRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
