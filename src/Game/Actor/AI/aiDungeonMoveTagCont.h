#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonMoveTagCont : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonMoveTagCont, ksys::act::ai::Ai)
public:
    explicit DungeonMoveTagCont(const InitArg& arg);
    ~DungeonMoveTagCont() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mMoveDis_m{};
    // map_unit_param at offset 0x40
    const float* mReturnDisFromCurrentPos_m{};
    // map_unit_param at offset 0x48
    const float* mReturnSpeedFromCurrentPos_m{};
};

}  // namespace uking::ai
