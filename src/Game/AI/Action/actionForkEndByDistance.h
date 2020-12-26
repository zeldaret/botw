#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEndByDistance : public Fork {
    SEAD_RTTI_OVERRIDE(ForkEndByDistance, Fork)
public:
    explicit ForkEndByDistance(const InitArg& arg);
    ~ForkEndByDistance() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const int* mEndMode_s{};
    // static_param at offset 0x40
    const float* mEndDist_s{};
    // static_param at offset 0x48
    const bool* mIsOnlyXZ_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
