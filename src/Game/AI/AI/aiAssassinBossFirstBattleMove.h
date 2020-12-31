#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossFirstBattleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinBossFirstBattleMove, ksys::act::ai::Ai)
public:
    explicit AssassinBossFirstBattleMove(const InitArg& arg);
    ~AssassinBossFirstBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDistXZ_s{};
    // static_param at offset 0x40
    const float* mCheckTargetDist_s{};
    // static_param at offset 0x48
    const float* mTooFarXZ_s{};
    // static_param at offset 0x50
    sead::SafeString mAnchorName_s{};
};

}  // namespace uking::ai
