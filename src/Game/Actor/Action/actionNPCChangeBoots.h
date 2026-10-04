#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCChangeBoots : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCChangeBoots, ksys::act::ai::Action)
public:
    explicit NPCChangeBoots(const InitArg& arg);
    ~NPCChangeBoots() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mBootsNumber_d{};
};

}  // namespace uking::action
