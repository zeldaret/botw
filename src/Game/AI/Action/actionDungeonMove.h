#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonMove, ksys::act::ai::Action)
public:
    explicit DungeonMove(const InitArg& arg);
    ~DungeonMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAccel_s{};
    // dynamic_param at offset 0x28
    float* mDynMoveDis_d{};
    // map_unit_param at offset 0x30
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x38
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x40
    const float* mMoveSpeed_m{};
    // map_unit_param at offset 0x48
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x50
    const float* mCameraRange_m{};
};

}  // namespace uking::action
