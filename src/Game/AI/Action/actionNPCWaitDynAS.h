#pragma once

#include "Game/AI/Action/actionNPCWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitDynAS : public NPCWait {
    SEAD_RTTI_OVERRIDE(NPCWaitDynAS, NPCWait)
public:
    explicit NPCWaitDynAS(const InitArg& arg);
    ~NPCWaitDynAS() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x40
    sead::SafeString mDynASName_d{};
};

}  // namespace uking::action
