#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSellHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSellHorse, ksys::act::ai::Action)
public:
    explicit NPCSellHorse(const InitArg& arg);
    ~NPCSellHorse() override;

protected:
};

}  // namespace uking::action
