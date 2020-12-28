#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaRoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaRoot, ksys::act::ai::Action)
public:
    explicit AreaRoot(const InitArg& arg);
    ~AreaRoot() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAutoSaveInterval_s{};
    // map_unit_param at offset 0x28
    const int* mCameraPriority_m{};
    // map_unit_param at offset 0x30
    const bool* mAutoSave_m{};
    // map_unit_param at offset 0x38
    const bool* mForceCalcInEvent_m{};
    // map_unit_param at offset 0x40
    sead::SafeString mCameraSet_m{};
    // map_unit_param at offset 0x50
    sead::SafeString mShape_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mWarpDestMapName_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mWarpDestPosName_m{};
};

}  // namespace uking::action
