#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendSignalForSignalFlowAct : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SendSignalForSignalFlowAct, ksys::act::ai::Action)
public:
    explicit SendSignalForSignalFlowAct(const InitArg& arg);
    ~SendSignalForSignalFlowAct() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mSignalType_d{};
    // dynamic_param at offset 0x28
    int* mValue_d{};
};

}  // namespace uking::action
