#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCNameHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCNameHorse, ksys::act::ai::Action)
public:
    explicit NPCNameHorse(const InitArg& arg);
    ~NPCNameHorse() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
