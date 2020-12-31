#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyLifted : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyLifted, ksys::act::ai::Ai)
public:
    explicit EnemyLifted(const InitArg& arg);
    ~EnemyLifted() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
