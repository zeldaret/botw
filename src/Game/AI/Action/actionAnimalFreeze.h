#pragma once

#include "Game/AI/Action/actionHorseFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalFreeze : public HorseFreeze {
    SEAD_RTTI_OVERRIDE(AnimalFreeze, HorseFreeze)
public:
    explicit AnimalFreeze(const InitArg& arg);
    ~AnimalFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
