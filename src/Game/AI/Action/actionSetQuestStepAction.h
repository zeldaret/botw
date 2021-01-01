#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetQuestStepAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetQuestStepAction, ksys::act::ai::Action)
public:
    explicit SetQuestStepAction(const InitArg& arg);
    ~SetQuestStepAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mForceRunTelop_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mQuestName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mStepName_d{};
};

}  // namespace uking::action
