#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonMoveTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonMoveTag, ksys::act::ai::Ai)
public:
    explicit DungeonMoveTag(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mInitDgnMoveDis_m{};
    // map_unit_param at offset 0x40
    const float* mMoveDis_m{};
};

}  // namespace uking::ai
