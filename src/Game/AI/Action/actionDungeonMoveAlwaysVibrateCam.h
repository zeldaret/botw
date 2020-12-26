#pragma once

#include "Game/AI/Action/actionDungeonMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonMoveAlwaysVibrateCam : public DungeonMove {
    SEAD_RTTI_OVERRIDE(DungeonMoveAlwaysVibrateCam, DungeonMove)
public:
    explicit DungeonMoveAlwaysVibrateCam(const InitArg& arg);
    ~DungeonMoveAlwaysVibrateCam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const bool* mIsSilentOnSuccess_s{};
    // map_unit_param at offset 0xa0
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0xa8
    const float* mCameraPower_m{};
    // map_unit_param at offset 0xb0
    const float* mCameraRange_m{};
};

}  // namespace uking::action
