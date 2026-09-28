#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/aiForkAI.h"

namespace ksys::act::ai {

class Fork4AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork4AI, ForkAI)
public:
    explicit Fork4AI(const InitArg& arg);
    ~Fork4AI() override;

protected:
};

}  // namespace ksys::act::ai
