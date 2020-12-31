#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyEscape : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyEscape, ksys::act::ai::Ai)
public:
    explicit EnemyEscape(const InitArg& arg);
    ~EnemyEscape() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
