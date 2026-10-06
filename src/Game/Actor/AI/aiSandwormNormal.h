#pragma once

#include "Game/Actor/AI/aiAwnSeal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormNormal : public AwnSeal {
    SEAD_RTTI_OVERRIDE(SandwormNormal, AwnSeal)
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
