#pragma once

#include "Game/AI/AI/aiRemainsRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsElectricRoot : public RemainsRoot {
    SEAD_RTTI_OVERRIDE(RemainsElectricRoot, RemainsRoot)
public:
    explicit RemainsElectricRoot(const InitArg& arg);
    ~RemainsElectricRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
