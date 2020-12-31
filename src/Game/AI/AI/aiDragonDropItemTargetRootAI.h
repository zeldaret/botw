#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonDropItemTargetRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DragonDropItemTargetRootAI, ksys::act::ai::Ai)
public:
    explicit DragonDropItemTargetRootAI(const InitArg& arg);
    ~DragonDropItemTargetRootAI() override;

protected:
};

}  // namespace uking::ai
