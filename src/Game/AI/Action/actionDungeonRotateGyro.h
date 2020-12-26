#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotateGyro : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonRotateGyro, ksys::act::ai::Action)
public:
    explicit DungeonRotateGyro(const InitArg& arg);
    ~DungeonRotateGyro() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSlerpRatio_s{};
    // static_param at offset 0x28
    const bool* mIsUseInstParamSlerpRatio_s{};
    // map_unit_param at offset 0x30
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x38
    const float* mGyroSlerpRatio_m{};
};

}  // namespace uking::action
