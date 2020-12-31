#pragma once

#include "Game/AI/AI/aiPriestBossFormation.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossLineFormationFall : public PriestBossFormation {
    SEAD_RTTI_OVERRIDE(PriestBossLineFormationFall, PriestBossFormation)
public:
    explicit PriestBossLineFormationFall(const InitArg& arg);
    ~PriestBossLineFormationFall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const float* mWarpHightOffset_s{};
};

}  // namespace uking::ai
