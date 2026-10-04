#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventIncreasePorchItemAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventIncreasePorchItemAction, ksys::act::ai::Action)
public:
    explicit EventIncreasePorchItemAction(const InitArg& arg);
    ~EventIncreasePorchItemAction() override;

    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mValue_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mPorchItemName_d{};
};

}  // namespace uking::action
