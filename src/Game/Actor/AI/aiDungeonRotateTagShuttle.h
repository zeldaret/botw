#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTagShuttle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTagShuttle, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTagShuttle(const InitArg& arg);
    ~DungeonRotateTagShuttle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mInitDgnRotRad_m{};
};

}  // namespace uking::ai
