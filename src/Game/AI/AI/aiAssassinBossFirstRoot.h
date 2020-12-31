#pragma once

#include "Game/AI/AI/aiAssassinBossRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossFirstRoot : public AssassinBossRootBase {
    SEAD_RTTI_OVERRIDE(AssassinBossFirstRoot, AssassinBossRootBase)
public:
    explicit AssassinBossFirstRoot(const InitArg& arg);
    ~AssassinBossFirstRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
