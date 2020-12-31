#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(LynelNormal, LandHumEnemyNormal)
public:
    explicit LynelNormal(const InitArg& arg);
    ~LynelNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x400
    int* mLynelAreaAlarmPoint_a{};
    // aitree_variable at offset 0x408
    int* mLynelAIFlags_a{};
    // aitree_variable at offset 0x410
    int* mLynelNoticeAttackRepeatNum_a{};
};

}  // namespace uking::ai
