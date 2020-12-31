#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Fork4AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork4AI, ForkAI)
public:
    explicit Fork4AI(const InitArg& arg);
    ~Fork4AI() override;

protected:
};

}  // namespace uking::ai
