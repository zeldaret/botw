#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerCleaningAround : public PlayerAction {
    SEAD_RTTI_OVERRIDE(PlayerCleaningAround, PlayerAction)
public:
    explicit PlayerCleaningAround(const InitArg& arg);
    ~PlayerCleaningAround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mCleaningTime_s{};
};

}  // namespace uking::action
