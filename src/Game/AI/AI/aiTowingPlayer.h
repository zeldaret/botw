#pragma once

#include "Game/AI/AI/aiTowing.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TowingPlayer : public Towing {
    SEAD_RTTI_OVERRIDE(TowingPlayer, Towing)
public:
    explicit TowingPlayer(const InitArg& arg);
    ~TowingPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const float* mInterruptDef_s{};
    // static_param at offset 0xd0
    const float* mCheckPlayerStateDef_s{};
};

}  // namespace uking::ai
