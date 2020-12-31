#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Fork5AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork5AI, ForkAI)
public:
    explicit Fork5AI(const InitArg& arg);
    ~Fork5AI() override;

protected:
};

}  // namespace uking::ai
