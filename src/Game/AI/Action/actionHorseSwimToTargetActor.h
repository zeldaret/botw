#pragma once

#include "Game/AI/Action/actionHorseSwim.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseSwimToTargetActor : public HorseSwim {
    SEAD_RTTI_OVERRIDE(HorseSwimToTargetActor, HorseSwim)
public:
    explicit HorseSwimToTargetActor(const InitArg& arg);
    ~HorseSwimToTargetActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
