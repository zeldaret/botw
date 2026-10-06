#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonRotateTagApp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTagApp, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTagApp(const InitArg& arg);
    ~DungeonRotateTagApp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const float* mTiltAngle_m{};
};

}  // namespace uking::ai
