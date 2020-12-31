#pragma once

#include "Game/AI/AI/aiEnemyWarnNoticeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyWarnNoticeEndChase : public EnemyWarnNoticeSelect {
    SEAD_RTTI_OVERRIDE(EnemyWarnNoticeEndChase, EnemyWarnNoticeSelect)
public:
    explicit EnemyWarnNoticeEndChase(const InitArg& arg);
    ~EnemyWarnNoticeEndChase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
