#pragma once

#include "Game/AI/Action/actionSwarmFlyMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmFlyAttack : public SwarmFlyMove {
    SEAD_RTTI_OVERRIDE(SwarmFlyAttack, SwarmFlyMove)
public:
    explicit SwarmFlyAttack(const InitArg& arg);
    ~SwarmFlyAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    const int* mFailTimeInClosePos_s{};
    // static_param at offset 0x140
    const int* mApplyMaterialAnimNumPerFrame_s{};
    // static_param at offset 0x148
    const float* mApplyMaterialAnimDist_s{};
};

}  // namespace uking::action
