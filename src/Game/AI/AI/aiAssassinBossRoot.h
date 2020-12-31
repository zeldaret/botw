#pragma once

#include "Game/AI/AI/aiAssassinBossRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossRoot : public AssassinBossRootBase {
    SEAD_RTTI_OVERRIDE(AssassinBossRoot, AssassinBossRootBase)
public:
    explicit AssassinBossRoot(const InitArg& arg);
    ~AssassinBossRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x2b0
    const int* mIronBallNum_s{};
    // static_param at offset 0x2b8
    const int* mBattleAvoidNum_s{};
};

}  // namespace uking::ai
