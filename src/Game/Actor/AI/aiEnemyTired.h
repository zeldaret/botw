#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyTired : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyTired, ksys::act::ai::Ai)
public:
    explicit EnemyTired(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
