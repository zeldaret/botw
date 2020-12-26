#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCStartTurnToPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCStartTurnToPlayer, ksys::act::ai::Action)
public:
    explicit NPCStartTurnToPlayer(const InitArg& arg);
    ~NPCStartTurnToPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mTurnRange_d{};
};

}  // namespace uking::action
