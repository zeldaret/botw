#pragma once

#include "Game/AI/Action/actionNPCWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitDynAS : public NPCWait {
    SEAD_RTTI_OVERRIDE(NPCWaitDynAS, NPCWait)
public:
    explicit NPCWaitDynAS(const InitArg& arg);
    ~NPCWaitDynAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x40
    sead::SafeString* mDynASName_d{};
};

}  // namespace uking::action
