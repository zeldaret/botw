#pragma once

#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalASPlayWithLegTurn : public ForkAnimalASPlay {
    SEAD_RTTI_OVERRIDE(AnimalASPlayWithLegTurn, ForkAnimalASPlay)
public:
    explicit AnimalASPlayWithLegTurn(const InitArg& arg);
    ~AnimalASPlayWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mRotSpeed_s{};
    // static_param at offset 0x68
    const float* mRotAccRatio_s{};
    // static_param at offset 0x70
    const float* mRotRatio_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
