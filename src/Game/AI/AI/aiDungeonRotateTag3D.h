#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTag3D : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTag3D, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTag3D(const InitArg& arg);
    ~DungeonRotateTag3D() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTargetRad_s{};
    // map_unit_param at offset 0x40
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x48
    const int* mRemainsPartType_m{};
    // map_unit_param at offset 0x50
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x58
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x60
    const float* mCameraRange_m{};
};

}  // namespace uking::ai
