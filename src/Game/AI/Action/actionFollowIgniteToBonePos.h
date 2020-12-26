#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowIgniteToBonePos : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowIgniteToBonePos, RotateTurnToTarget)
public:
    explicit FollowIgniteToBonePos(const InitArg& arg);
    ~FollowIgniteToBonePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const float* mLocalOffSetX_s{};
    // static_param at offset 0x80
    const float* mLocalOffSetY_s{};
    // static_param at offset 0x88
    const float* mLocalOffSetZ_s{};
    // static_param at offset 0x90
    const bool* mIsIgnitePosYZero_s{};
    // static_param at offset 0x98
    sead::SafeString mBoneName_s{};
};

}  // namespace uking::action
