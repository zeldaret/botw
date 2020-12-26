#pragma once

#include "Game/AI/Action/actionPlayerLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLookAtObjectNow : public PlayerLookAtObject {
    SEAD_RTTI_OVERRIDE(PlayerLookAtObjectNow, PlayerLookAtObject)
public:
    explicit PlayerLookAtObjectNow(const InitArg& arg);
    ~PlayerLookAtObjectNow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
