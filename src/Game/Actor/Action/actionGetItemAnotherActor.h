#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GetItemAnotherActor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GetItemAnotherActor, ksys::act::ai::Action)
public:
    explicit GetItemAnotherActor(const InitArg& arg);
    ~GetItemAnotherActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mGetActorName_d{};
    // aitree_variable at offset 0x30
    int* mGetNumLeft_a{};
};

}  // namespace uking::action
