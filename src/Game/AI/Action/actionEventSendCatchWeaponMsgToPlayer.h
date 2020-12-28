#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSendCatchWeaponMsgToPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSendCatchWeaponMsgToPlayer, ksys::act::ai::Action)
public:
    explicit EventSendCatchWeaponMsgToPlayer(const InitArg& arg);
    ~EventSendCatchWeaponMsgToPlayer() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
