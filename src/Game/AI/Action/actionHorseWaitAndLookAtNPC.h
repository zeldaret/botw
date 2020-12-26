#pragma once

#include "Game/AI/Action/actionHorseWaitAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseWaitAndLookAtNPC : public HorseWaitAction {
    SEAD_RTTI_OVERRIDE(HorseWaitAndLookAtNPC, HorseWaitAction)
public:
    explicit HorseWaitAndLookAtNPC(const InitArg& arg);
    ~HorseWaitAndLookAtNPC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
