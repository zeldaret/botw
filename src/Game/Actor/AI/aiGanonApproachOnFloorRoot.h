#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonApproachOnFloorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonApproachOnFloorRoot, ksys::act::ai::Ai)
public:
    explicit GanonApproachOnFloorRoot(const InitArg& arg);
    ~GanonApproachOnFloorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFinDist_s{};
    // static_param at offset 0x40
    const float* mApproachTime_s{};
    // static_param at offset 0x48
    const float* mFinFarDist_s{};
    // static_param at offset 0x50
    const float* mMoveFrontRate_s{};
    // static_param at offset 0x58
    const float* mMoveFrontLRRate_s{};
    // static_param at offset 0x60
    const float* mMoveBackLRRate_s{};
    // static_param at offset 0x68
    const float* mCloseDist_s{};
    // static_param at offset 0x70
    const float* mForbitAngMin_s{};
    // static_param at offset 0x78
    const float* mForbitAngMax_s{};
    // static_param at offset 0x80
    const float* mCheckPosAng0_s{};
    // static_param at offset 0x88
    const float* mCheckPosAng1_s{};
    // static_param at offset 0x90
    const float* mCheckPosAng2_s{};
    // static_param at offset 0x98
    const float* mCheckPosAng3_s{};
    // static_param at offset 0xa0
    const float* mCheckPosAng4_s{};
    // dynamic_param at offset 0xa8
    bool* mIsMoveSide_d{};
    // dynamic_param at offset 0xb0
    bool* mIsChangeable_d{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mMoveDstPos_d{};
};

}  // namespace uking::ai
