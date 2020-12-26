#pragma once

#include "Game/AI/Action/actionFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmFlyMove : public FlyMoveBase {
    SEAD_RTTI_OVERRIDE(SwarmFlyMove, FlyMoveBase)
public:
    explicit SwarmFlyMove(const InitArg& arg);
    ~SwarmFlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mIgnoreSensorTime_s{};
    // static_param at offset 0xc8
    const float* mSubAccRateMin_s{};
    // static_param at offset 0xd0
    const float* mSubAccRateMax_s{};
    // static_param at offset 0xd8
    const float* mMaterialAnimFrame_s{};
    // static_param at offset 0xe0
    sead::SafeString mMaterialAnimName_s{};
};

}  // namespace uking::action
