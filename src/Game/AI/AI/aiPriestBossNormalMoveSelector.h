#pragma once

#include "Game/AI/AI/aiPriestBossMode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossNormalMoveSelector : public PriestBossMode {
    SEAD_RTTI_OVERRIDE(PriestBossNormalMoveSelector, PriestBossMode)
public:
    explicit PriestBossNormalMoveSelector(const InitArg& arg);
    ~PriestBossNormalMoveSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x40
    sead::Vector3f* mMoveTargetPos_d{};
};

}  // namespace uking::ai
