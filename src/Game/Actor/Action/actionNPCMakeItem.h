#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCMakeItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCMakeItem, ksys::act::ai::Action)
public:
    explicit NPCMakeItem(const InitArg& arg);
    ~NPCMakeItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mShopType_d{};
    // dynamic_param at offset 0x28
    bool* mIncludePorch_d{};
};

}  // namespace uking::action
