#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCHorseReception : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCHorseReception, ksys::act::ai::Action)
public:
    explicit NPCHorseReception(const InitArg& arg);
    ~NPCHorseReception() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
