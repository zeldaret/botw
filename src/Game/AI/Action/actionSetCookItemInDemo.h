#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetCookItemInDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetCookItemInDemo, ksys::act::ai::Action)
public:
    explicit SetCookItemInDemo(const InitArg& arg);
    ~SetCookItemInDemo() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mSetNum_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mPorchItemName01_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mPorchItemName02_d{};
    // dynamic_param at offset 0x48
    sead::SafeString mPorchItemName03_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mPorchItemName04_d{};
    // dynamic_param at offset 0x68
    sead::SafeString mPorchItemName05_d{};
};

}  // namespace uking::action
