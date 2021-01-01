#pragma once

#include "Game/AI/Action/actionNPCLerpAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCLerpDynAS : public NPCLerpAction {
    SEAD_RTTI_OVERRIDE(NPCLerpDynAS, NPCLerpAction)
public:
    explicit NPCLerpDynAS(const InitArg& arg);
    ~NPCLerpDynAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xa8
    sead::SafeString mDynASName_d{};
};

}  // namespace uking::action
