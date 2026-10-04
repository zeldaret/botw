#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCChasePlayerBlueFire : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCChasePlayerBlueFire, ksys::act::ai::Ai)
public:
    explicit NPCChasePlayerBlueFire(const InitArg& arg);
    ~NPCChasePlayerBlueFire() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const float* mNearDist_s{};
    // static_param at offset 0x48
    const float* mLeaveDist_s{};
    // static_param at offset 0x50
    const float* mLostDist_s{};
};

}  // namespace uking::ai
