#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventRollbackQuestAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventRollbackQuestAction, ksys::act::ai::Action)
public:
    explicit EventRollbackQuestAction(const InitArg& arg);
    ~EventRollbackQuestAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mQuestName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mStepName_d{};
};

}  // namespace uking::action
