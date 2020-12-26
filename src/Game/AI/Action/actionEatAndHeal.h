#pragma once

#include "Game/AI/Action/actionAnimalEatAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EatAndHeal : public AnimalEatAction {
    SEAD_RTTI_OVERRIDE(EatAndHeal, AnimalEatAction)
public:
    explicit EatAndHeal(const InitArg& arg);
    ~EatAndHeal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
