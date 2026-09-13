#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KokkoMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(KokkoMove, ksys::act::ai::Action)
public:
    explicit KokkoMove(const InitArg& arg);
    ~KokkoMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mAngularSpeed_s{};
    // static_param at offset 0x30
    const float* mNavMeshGoalDistanceTolerance_s{};
    // static_param at offset 0x38
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x40
    const bool* mIsCancelRequestedPathFirst_s{};
    // static_param at offset 0x48
    const bool* mIsChangeable_s{};
    // static_param at offset 0x50
    const bool* mAvoidPlayer_s{};
    // static_param at offset 0x58
    const bool* mUseLocalSteering_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
