#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(ForestGiantNormal, EnemyNormal)
public:
    explicit ForestGiantNormal(const InitArg& arg);
    ~ForestGiantNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3d0
    const float* mSleepingHearAwnRatio_s{};
};

}  // namespace uking::ai
