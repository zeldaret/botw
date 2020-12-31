#pragma once

#include "Game/AI/AI/aiMimicCliffStopEnemyNormalBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicCliffStopEnemyNormal : public MimicCliffStopEnemyNormalBase {
    SEAD_RTTI_OVERRIDE(MimicCliffStopEnemyNormal, MimicCliffStopEnemyNormalBase)
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
