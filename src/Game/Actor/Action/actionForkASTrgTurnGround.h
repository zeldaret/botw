#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgTurnGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgTurnGround, ksys::act::ai::Action)
public:
    explicit ForkASTrgTurnGround(const InitArg& arg);
    ~ForkASTrgTurnGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeedBasePosRatio_s{};
    // static_param at offset 0x28
    const float* mOnAfterGroundRotAngle_s{};
    // static_param at offset 0x30
    const sead::Vector3f* mAxis_s{};
    // static_param at offset 0x38
    const sead::Vector3f* mCtrlOffset_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mCtrlAngleOffset_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mActMoveVec_s{};
    // aitree_variable at offset 0x50
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
