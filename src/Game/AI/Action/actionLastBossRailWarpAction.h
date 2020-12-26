#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossRailWarpAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossRailWarpAction, ksys::act::ai::Action)
public:
    explicit LastBossRailWarpAction(const InitArg& arg);
    ~LastBossRailWarpAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWarpTime_s{};
    // static_param at offset 0x28
    const float* mYOffset_s{};
    // static_param at offset 0x30
    const bool* mIsUpdateHomePos_s{};
    // static_param at offset 0x38
    const bool* mIsTurnToPlayer_s{};
    // dynamic_param at offset 0x40
    int* mRailIndex_d{};
    // dynamic_param at offset 0x48
    bool* mIsPartsActorTgOn_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
