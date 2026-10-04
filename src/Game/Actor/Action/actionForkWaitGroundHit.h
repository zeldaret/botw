#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWaitGroundHit : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkWaitGroundHit, ksys::act::ai::Action)
public:
    explicit ForkWaitGroundHit(const InitArg& arg);
    ~ForkWaitGroundHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const bool* mIsChangeable_s{};
};

}  // namespace uking::action
