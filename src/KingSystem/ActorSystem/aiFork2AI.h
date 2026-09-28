#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/aiForkAI.h"

namespace ksys::act::ai {

class Fork2AI : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork2AI, ForkAI)
public:
    explicit Fork2AI(const InitArg& arg);
    ~Fork2AI() override;

protected:
};

}  // namespace ksys::act::ai
