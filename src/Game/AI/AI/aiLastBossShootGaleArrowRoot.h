#pragma once

#include "Game/AI/AI/aiLastBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastBossShootGaleArrowRoot : public LastBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(LastBossShootGaleArrowRoot, LastBossShootNormalArrowRoot)
public:
    explicit LastBossShootGaleArrowRoot(const InitArg& arg);
    ~LastBossShootGaleArrowRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
