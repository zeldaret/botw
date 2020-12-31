#pragma once

#include "Game/AI/AI/aiSwarmRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeeSwarmRoot : public SwarmRoot {
    SEAD_RTTI_OVERRIDE(BeeSwarmRoot, SwarmRoot)
public:
    explicit BeeSwarmRoot(const InitArg& arg);
    ~BeeSwarmRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
