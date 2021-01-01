#pragma once

#include "Game/AI/Action/actionNPCTargetMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCTargetMoveDynAs : public NPCTargetMove {
    SEAD_RTTI_OVERRIDE(NPCTargetMoveDynAs, NPCTargetMove)
public:
    explicit NPCTargetMoveDynAs(const InitArg& arg);
    ~NPCTargetMoveDynAs() override;

    void loadParams_() override;

protected:
    // dynamic_param at offset 0x178
    sead::SafeString mDynASKeyName_d{};
};

}  // namespace uking::action
