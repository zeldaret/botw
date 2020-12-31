#pragma once

#include "Game/AI/AI/aiEnemyNoticeTerror.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeFearfulTarget : public EnemyNoticeTerror {
    SEAD_RTTI_OVERRIDE(EnemyNoticeFearfulTarget, EnemyNoticeTerror)
public:
    explicit EnemyNoticeFearfulTarget(const InitArg& arg);
    ~EnemyNoticeFearfulTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
