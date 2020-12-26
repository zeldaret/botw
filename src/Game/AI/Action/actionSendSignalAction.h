#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendSignalAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SendSignalAction, ksys::act::ai::Action)
public:
    explicit SendSignalAction(const InitArg& arg);
    ~SendSignalAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mSignalType_d{};
    // dynamic_param at offset 0x28
    bool* mValue_d{};
};

}  // namespace uking::action
