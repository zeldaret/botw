#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Fork2AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork2AI, ForkAI)
public:
    explicit Fork2AI(const InitArg& arg);
    ~Fork2AI() override;

protected:
};

}  // namespace uking::ai
