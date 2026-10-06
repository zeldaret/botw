#pragma once

#include "Game/Actor/AI/aiCliffStopEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicCliffStopEnemyNormal : public CliffStopEnemyNormal {
    SEAD_RTTI_OVERRIDE(MimicCliffStopEnemyNormal, CliffStopEnemyNormal)
public:
    explicit MimicCliffStopEnemyNormal(const InitArg& arg);
    ~MimicCliffStopEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1e0
    const float* mJumpDistXZ_s{};
};

}  // namespace uking::ai
