#pragma once

#include "Game/AI/Action/actionSimpleLineBeam.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonBeastBeamMove : public SimpleLineBeam {
    SEAD_RTTI_OVERRIDE(GanonBeastBeamMove, SimpleLineBeam)
public:
    explicit GanonBeastBeamMove(const InitArg& arg);
    ~GanonBeastBeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x230
    const int* mRestDistTime_s{};
    // static_param at offset 0x238
    const int* mRestDistTimeAdd_s{};
    // static_param at offset 0x240
    const int* mRestNumMax_s{};
    // static_param at offset 0x248
    const float* mRestDistLimit_s{};
    // static_param at offset 0x250
    const float* mRestDistMinLimit_s{};
    // static_param at offset 0x258
    const float* mRestDistInterval_s{};
    // static_param at offset 0x260
    sead::SafeString mRestActor_s{};
};

}  // namespace uking::action
