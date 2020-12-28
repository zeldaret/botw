#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCInfoOnNamedHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCInfoOnNamedHorse, ksys::act::ai::Action)
public:
    explicit NPCInfoOnNamedHorse(const InitArg& arg);
    ~NPCInfoOnNamedHorse() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
