#pragma once

#include "Game/AI/AI/aiEnemyLost.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormLost : public EnemyLost {
    SEAD_RTTI_OVERRIDE(SandwormLost, EnemyLost)
public:
    explicit SandwormLost(const InitArg& arg);
    ~SandwormLost() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const float* mDiveSandOffset_s{};
};

}  // namespace uking::ai
