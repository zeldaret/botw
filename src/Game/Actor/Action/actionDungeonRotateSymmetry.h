#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotateSymmetry : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonRotateSymmetry, ksys::act::ai::Action)
public:
    explicit DungeonRotateSymmetry(const InitArg& arg);
    ~DungeonRotateSymmetry() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x28
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x30
    const int* mRemainsPartType_m{};
    // map_unit_param at offset 0x38
    const float* mTiltAngle_m{};
    // map_unit_param at offset 0x40
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x48
    const float* mInitDgnRotRad_m{};
    // map_unit_param at offset 0x50
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x58
    const float* mCameraRange_m{};
};

}  // namespace uking::action
