#pragma once

#include "Game/AI/AI/aiWeakPointRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemWeakPointRoot : public WeakPointRoot {
    SEAD_RTTI_OVERRIDE(GolemWeakPointRoot, WeakPointRoot)
public:
    explicit GolemWeakPointRoot(const InitArg& arg);
    ~GolemWeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
