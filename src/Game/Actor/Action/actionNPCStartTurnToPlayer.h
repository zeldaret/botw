#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCStartTurnToPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCStartTurnToPlayer, ksys::act::ai::Action)
public:
    explicit NPCStartTurnToPlayer(const InitArg& arg);
    ~NPCStartTurnToPlayer() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;

    // dynamic_param at offset 0x20
    float* mTurnRange_d{};

    float mValue;
};

}  // namespace uking::action
