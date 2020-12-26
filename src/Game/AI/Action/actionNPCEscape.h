#pragma once

#include "Game/AI/Action/actionRandomMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCEscape : public RandomMoveAction {
    SEAD_RTTI_OVERRIDE(NPCEscape, RandomMoveAction)
public:
    explicit NPCEscape(const InitArg& arg);
    ~NPCEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const int* mWallHitTime_s{};
    // static_param at offset 0x40
    const int* mStopTime_s{};
    // static_param at offset 0x48
    const float* mMaxDistance_s{};
    // static_param at offset 0x50
    const float* mMinDistance_s{};
    // static_param at offset 0x58
    const float* mAngularRange_s{};
    // static_param at offset 0x60
    const float* mVerticalEscapeSpeed_s{};
    // static_param at offset 0x68
    const bool* mIsTurnToTargetPos_s{};
    // static_param at offset 0x70
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetVel_d{};
    // map_unit_param at offset 0xc0
    const float* mTerritoryArea_m{};
};

}  // namespace uking::action
