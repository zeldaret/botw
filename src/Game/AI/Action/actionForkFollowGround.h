#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkFollowGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkFollowGround, ksys::act::ai::Action)
public:
    explicit ForkFollowGround(const InitArg& arg);
    ~ForkFollowGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mUpdateFrameCountAfterNoMove_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x38
    const float* mUpdateTargetUpDirMinAngle_s{};
    // static_param at offset 0x40
    const float* mUpdateTargetUpDirRatio_s{};
};

}  // namespace uking::action
