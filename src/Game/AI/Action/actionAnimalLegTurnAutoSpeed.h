#pragma once

#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalLegTurnAutoSpeed : public ForkAnimalASPlay {
    SEAD_RTTI_OVERRIDE(AnimalLegTurnAutoSpeed, ForkAnimalASPlay)
public:
    explicit AnimalLegTurnAutoSpeed(const InitArg& arg);
    ~AnimalLegTurnAutoSpeed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
