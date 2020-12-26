#pragma once

#include "Game/AI/Action/actionPlayerAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoPlayerZoraRide : public PlayerAction {
    SEAD_RTTI_OVERRIDE(DemoPlayerZoraRide, PlayerAction)
public:
    explicit DemoPlayerZoraRide(const InitArg& arg);
    ~DemoPlayerZoraRide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
