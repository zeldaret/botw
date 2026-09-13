#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonMoveReset : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonMoveReset, ksys::act::ai::Action)
public:
    explicit DungeonMoveReset(const InitArg& arg);
    ~DungeonMoveReset() override;

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
    // dynamic_param at offset 0x30
    float* mDynMoveSpeed_d{};
    // map_unit_param at offset 0x38
    const int* mInitDgnPriority_m{};
};

}  // namespace uking::action
