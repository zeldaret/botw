#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetTreasure : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetTreasure, ksys::act::ai::Action)
public:
    explicit SetTreasure(const InitArg& arg);
    ~SetTreasure() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
    // aitree_variable at offset 0x30
    sead::SafeString* mDropActorName_a{};
};

}  // namespace uking::action
