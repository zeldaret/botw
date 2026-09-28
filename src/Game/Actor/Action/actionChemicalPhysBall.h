#pragma once

#include "Game/Actor/Action/actionChemicalAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalPhysBall : public ChemicalAttack {
    SEAD_RTTI_OVERRIDE(ChemicalPhysBall, ChemicalAttack)
public:
    explicit ChemicalPhysBall(const InitArg& arg);
    ~ChemicalPhysBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mDeleteTime_s{};
};

}  // namespace uking::action
