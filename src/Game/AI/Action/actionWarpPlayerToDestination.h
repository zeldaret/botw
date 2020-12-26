#pragma once

#include "Game/AI/Action/actionWarpPlayerBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerToDestination : public WarpPlayerBase {
    SEAD_RTTI_OVERRIDE(WarpPlayerToDestination, WarpPlayerBase)
public:
    explicit WarpPlayerToDestination(const InitArg& arg);
    ~WarpPlayerToDestination() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x60
    float* mDestinationX_d{};
    // dynamic_param at offset 0x68
    float* mDestinationY_d{};
    // dynamic_param at offset 0x70
    float* mDestinationZ_d{};
    // dynamic_param at offset 0x78
    float* mDirectionY_d{};
};

}  // namespace uking::action
