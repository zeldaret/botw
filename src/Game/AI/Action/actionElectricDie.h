#pragma once

#include "Game/AI/Action/actionElectricBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ElectricDie : public ElectricBlownOff {
    SEAD_RTTI_OVERRIDE(ElectricDie, ElectricBlownOff)
public:
    explicit ElectricDie(const InitArg& arg);
    ~ElectricDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
