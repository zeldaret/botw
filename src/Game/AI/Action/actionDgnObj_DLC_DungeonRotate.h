#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DgnObj_DLC_DungeonRotate : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_DungeonRotate, DungeonRotateBase)
public:
    explicit DgnObj_DLC_DungeonRotate(const InitArg& arg);
    ~DgnObj_DLC_DungeonRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0xc8
    const float* mGearRatio_m{};
    // map_unit_param at offset 0xd0
    const bool* mIsClockWiseRotation_m{};
    // aitree_variable at offset 0xd8
    float* mRotationOffset_a{};
};

}  // namespace uking::action
