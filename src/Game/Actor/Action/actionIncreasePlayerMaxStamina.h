#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IncreasePlayerMaxStamina : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IncreasePlayerMaxStamina, ksys::act::ai::Action)
public:
    explicit IncreasePlayerMaxStamina(const InitArg& arg);
    ~IncreasePlayerMaxStamina() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mValue_d{};
    // dynamic_param at offset 0x28
    bool* mIsMoveCenter_d{};
};

}  // namespace uking::action
