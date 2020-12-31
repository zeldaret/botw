#pragma once

#include "Game/AI/AI/aiEnemyNoticeSoundSensitive.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeSoundSensitiveTimer : public EnemyNoticeSoundSensitive {
    SEAD_RTTI_OVERRIDE(EnemyNoticeSoundSensitiveTimer, EnemyNoticeSoundSensitive)
public:
    explicit EnemyNoticeSoundSensitiveTimer(const InitArg& arg);
    ~EnemyNoticeSoundSensitiveTimer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x70
    const int* mTimer_s{};
};

}  // namespace uking::ai
