#pragma once

#include "Game/AI/AI/aiEnemyNoticeSound.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNoticeSoundWithUI : public EnemyNoticeSound {
    SEAD_RTTI_OVERRIDE(EnemyNoticeSoundWithUI, EnemyNoticeSound)
public:
    explicit EnemyNoticeSoundWithUI(const InitArg& arg);
    ~EnemyNoticeSoundWithUI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
