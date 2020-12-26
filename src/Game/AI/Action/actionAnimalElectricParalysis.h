#pragma once

#include "Game/AI/Action/actionHorseElectricParalysis.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalElectricParalysis : public HorseElectricParalysis {
    SEAD_RTTI_OVERRIDE(AnimalElectricParalysis, HorseElectricParalysis)
public:
    explicit AnimalElectricParalysis(const InitArg& arg);
    ~AnimalElectricParalysis() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
