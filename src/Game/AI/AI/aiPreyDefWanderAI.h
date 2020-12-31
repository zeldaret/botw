#pragma once

#include "Game/AI/AI/aiDefWanderAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyDefWanderAI : public DefWanderAI {
    SEAD_RTTI_OVERRIDE(PreyDefWanderAI, DefWanderAI)
public:
    explicit PreyDefWanderAI(const InitArg& arg);
    ~PreyDefWanderAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const int* mTimesStuckLimit_s{};
    // static_param at offset 0x88
    const float* mFramesStuckLimit_s{};
    // aitree_variable at offset 0x90
    float* mFramesStuckOnTerrain_a{};
    // aitree_variable at offset 0x98
    bool* mIsStuckOnTerrain_a{};
};

}  // namespace uking::ai
