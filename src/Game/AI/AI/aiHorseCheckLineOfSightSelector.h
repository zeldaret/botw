#pragma once

#include "Game/AI/AI/aiHorseCheckLineOfSightSelectorBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseCheckLineOfSightSelector : public HorseCheckLineOfSightSelectorBase {
    SEAD_RTTI_OVERRIDE(HorseCheckLineOfSightSelector, HorseCheckLineOfSightSelectorBase)
public:
    explicit HorseCheckLineOfSightSelector(const InitArg& arg);
    ~HorseCheckLineOfSightSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
