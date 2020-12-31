#pragma once

#include "Game/AI/AI/aiTargetDistanceSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetActorDistanceSelect : public TargetDistanceSelect {
    SEAD_RTTI_OVERRIDE(TargetActorDistanceSelect, TargetDistanceSelect)
public:
    explicit TargetActorDistanceSelect(const InitArg& arg);
    ~TargetActorDistanceSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
