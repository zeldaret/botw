#pragma once

#include "Game/AI/Action/actionNPCWaitAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NpcRideWaitAction : public NPCWaitAction {
    SEAD_RTTI_OVERRIDE(NpcRideWaitAction, NPCWaitAction)
public:
    explicit NpcRideWaitAction(const InitArg& arg);
    ~NpcRideWaitAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x38
    float* mGearSpeed_d{};
};

}  // namespace uking::action
