#pragma once

#include "Game/AI/AI/aiAssassinMiddleAzitoRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleAzitoDlcRoot : public AssassinMiddleAzitoRoot {
    SEAD_RTTI_OVERRIDE(AssassinMiddleAzitoDlcRoot, AssassinMiddleAzitoRoot)
public:
    explicit AssassinMiddleAzitoDlcRoot(const InitArg& arg);
    ~AssassinMiddleAzitoDlcRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
