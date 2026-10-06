#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/aiForkAI.h"

namespace ksys::act::ai {

class Fork6AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork6AI, ForkAI)
public:
    explicit Fork6AI(const InitArg& arg);
    ~Fork6AI() override;

protected:
};

}  // namespace ksys::act::ai
