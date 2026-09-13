#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonCannonBallAutoDelete : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonCannonBallAutoDelete, ksys::act::ai::Ai)
public:
    explicit DungeonCannonBallAutoDelete(const InitArg& arg);
    ~DungeonCannonBallAutoDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTriggerVelocityKeepTime_s{};
    // static_param at offset 0x40
    const float* mTriggerVelocity_s{};
};

}  // namespace uking::ai
