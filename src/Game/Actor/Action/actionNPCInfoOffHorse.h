#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCInfoOffHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCInfoOffHorse, ksys::act::ai::Action)
public:
    explicit NPCInfoOffHorse(const InitArg& arg);
    ~NPCInfoOffHorse() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
