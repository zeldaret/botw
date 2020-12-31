#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Fork3AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork3AI, ForkAI)
public:
    explicit Fork3AI(const InitArg& arg);
    ~Fork3AI() override;

protected:
};

}  // namespace uking::ai
