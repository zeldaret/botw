#pragma once

#include "Game/AI/AI/aiSandwormNormalBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormNormal : public SandwormNormalBase {
    SEAD_RTTI_OVERRIDE(SandwormNormal, SandwormNormalBase)
public:
    explicit SandwormNormal(const InitArg& arg);
    ~SandwormNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
