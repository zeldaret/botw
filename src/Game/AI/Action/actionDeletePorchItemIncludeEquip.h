#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DeletePorchItemIncludeEquip : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DeletePorchItemIncludeEquip, ksys::act::ai::Action)
public:
    explicit DeletePorchItemIncludeEquip(const InitArg& arg);
    ~DeletePorchItemIncludeEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mDeleteNum_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mPorchItemName_d{};
};

}  // namespace uking::action
