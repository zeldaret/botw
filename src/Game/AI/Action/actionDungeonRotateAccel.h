#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotateAccel : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotateAccel, DungeonRotateBase)
public:
    explicit DungeonRotateAccel(const InitArg& arg);
    ~DungeonRotateAccel() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc8
    const bool* mIsSlowDown_s{};
    // dynamic_param at offset 0xd0
    float* mDynCurrentAngVel_d{};
    // dynamic_param at offset 0xd8
    float* mDynAngAccel_d{};
};

}  // namespace uking::action
