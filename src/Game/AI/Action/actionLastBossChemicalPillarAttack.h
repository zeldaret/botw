#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossChemicalPillarAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossChemicalPillarAttack, ksys::act::ai::Action)
public:
    explicit LastBossChemicalPillarAttack(const InitArg& arg);
    ~LastBossChemicalPillarAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mPillarNum_s{};
    // static_param at offset 0x28
    const float* mAttackEndWait_s{};
    // static_param at offset 0x30
    const float* mCreateInterval_s{};
    // static_param at offset 0x38
    const float* mPillarYOffset_s{};
};

}  // namespace uking::action
