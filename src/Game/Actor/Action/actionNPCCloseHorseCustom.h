#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCCloseHorseCustom : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCCloseHorseCustom, ksys::act::ai::Action)
public:
    explicit NPCCloseHorseCustom(const InitArg& arg);
    ~NPCCloseHorseCustom() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
