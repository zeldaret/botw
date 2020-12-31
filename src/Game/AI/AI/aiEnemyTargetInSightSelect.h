#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyTargetInSightSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyTargetInSightSelect, ksys::act::ai::Ai)
public:
    explicit EnemyTargetInSightSelect(const InitArg& arg);
    ~EnemyTargetInSightSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
