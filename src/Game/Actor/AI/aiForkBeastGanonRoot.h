#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/aiForkAI.h"

namespace uking::ai {

class ForkBeastGanonRoot : public ksys::act::ai::ForkAI {
    SEAD_RTTI_OVERRIDE(ForkBeastGanonRoot, ksys::act::ai::ForkAI)
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
