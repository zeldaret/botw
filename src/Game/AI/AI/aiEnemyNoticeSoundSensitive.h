#pragma once

#include "Game/AI/AI/aiEnemyNoticeSoundWithUI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeSoundSensitive : public EnemyNoticeSoundWithUI {
    SEAD_RTTI_OVERRIDE(EnemyNoticeSoundSensitive, EnemyNoticeSoundWithUI)
public:
    explicit EnemyNoticeSoundSensitive(const InitArg& arg);
    ~EnemyNoticeSoundSensitive() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
