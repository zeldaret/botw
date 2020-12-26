#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NpcTebaFly : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NpcTebaFly, ksys::act::ai::Action)
public:
    explicit NpcTebaFly(const InitArg& arg);
    ~NpcTebaFly() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTurnEnableFrame_s{};
    // static_param at offset 0x28
    const float* mStartTurnDist_s{};
    // static_param at offset 0x30
    const float* mTurnSpeed_s{};
    // static_param at offset 0x38
    const float* mInterpolateTurnFrameForMaxSpeed_s{};
    // static_param at offset 0x40
    const float* mInterpolateMoveFrameForMaxSpeed_s{};
    // static_param at offset 0x48
    const float* mTurnEndRad_s{};
    // static_param at offset 0x50
    const float* mMoveSpeedMin_s{};
    // static_param at offset 0x58
    const float* mMoveSpeedMax_s{};
    // static_param at offset 0x60
    const float* mTurnReduceSpeedRatio_s{};
    // static_param at offset 0x68
    const float* mEvacuateRemainsDist_s{};
    // static_param at offset 0x70
    const float* mTargetPosRatio_s{};
    // static_param at offset 0x78
    const float* mPlayerApproachCannonDist_s{};
};

}  // namespace uking::action
