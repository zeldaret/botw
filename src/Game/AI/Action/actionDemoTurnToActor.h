#pragma once

#include "Game/AI/Action/actionTurnToActor.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoTurnToActor : public TurnToActor {
    SEAD_RTTI_OVERRIDE(DemoTurnToActor, TurnToActor)
public:
    explicit DemoTurnToActor(const InitArg& arg);
    ~DemoTurnToActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x60
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mUniqueName_d{};
};

}  // namespace uking::action
