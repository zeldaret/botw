#pragma once

#include "Game/Actor/AI/aiCheckLineOfSightSelector.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseCheckLineOfSightSelector : public CheckLineOfSightSelector {
    SEAD_RTTI_OVERRIDE(HorseCheckLineOfSightSelector, CheckLineOfSightSelector)
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
