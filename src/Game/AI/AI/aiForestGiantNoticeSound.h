#pragma once

#include "Game/AI/AI/aiEnemyNoticeSound.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantNoticeSound : public EnemyNoticeSound {
    SEAD_RTTI_OVERRIDE(ForestGiantNoticeSound, EnemyNoticeSound)
public:
    explicit ForestGiantNoticeSound(const InitArg& arg);
    ~ForestGiantNoticeSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x48
    const float* mFrontAngle_s{};
    // static_param at offset 0x50
    const bool* mUseSimpleOffset_s{};
};

}  // namespace uking::ai
