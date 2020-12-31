#pragma once

#include "Game/AI/AI/aiGolemWeakPointRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemRWeakPointRoot : public GolemWeakPointRoot {
    SEAD_RTTI_OVERRIDE(GolemRWeakPointRoot, GolemWeakPointRoot)
public:
    explicit GolemRWeakPointRoot(const InitArg& arg);
    ~GolemRWeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
