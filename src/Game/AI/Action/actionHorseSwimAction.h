#pragma once

#include "Game/AI/Action/actionHorseSwim.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseSwimAction : public HorseSwim {
    SEAD_RTTI_OVERRIDE(HorseSwimAction, HorseSwim)
public:
    explicit HorseSwimAction(const InitArg& arg);
    ~HorseSwimAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mLandSearchRadius_s{};
    // static_param at offset 0x28
    const float* mLandSearchNormalCos_s{};
    // static_param at offset 0x30
    const float* mLandSearchMinArea_s{};
    // static_param at offset 0x38
    const float* mLandSearchIntervalFrames_s{};
    // static_param at offset 0x40
    const float* mResolvePenetrationRadiusScale_s{};
    // static_param at offset 0x48
    const float* mResolvePenetrationSearchRadius_s{};
};

}  // namespace uking::action
