#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonRotateShuttle : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DungeonRotateShuttle, DungeonRotateBase)
public:
    explicit DungeonRotateShuttle(const InitArg& arg);
    ~DungeonRotateShuttle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc8
    const int* mRotDir_s{};
    // map_unit_param at offset 0xd0
    const float* mTiltAngle_m{};
};

}  // namespace uking::action
