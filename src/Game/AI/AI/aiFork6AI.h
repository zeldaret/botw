#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Fork6AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork6AI, ForkAI)
public:
    explicit Fork6AI(const InitArg& arg);
    ~Fork6AI() override;

protected:
};

}  // namespace uking::ai
