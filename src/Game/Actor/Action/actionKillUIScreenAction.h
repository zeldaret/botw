#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KillUIScreenAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(KillUIScreenAction, ksys::act::ai::Action)
public:
    explicit KillUIScreenAction(const InitArg& arg);
    ~KillUIScreenAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mScreenName_d{};
};

}  // namespace uking::action
