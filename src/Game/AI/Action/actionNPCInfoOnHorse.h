#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCInfoOnHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCInfoOnHorse, ksys::act::ai::Action)
public:
    explicit NPCInfoOnHorse(const InitArg& arg);
    ~NPCInfoOnHorse() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
