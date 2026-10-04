#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BocoblinBackStepAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BocoblinBackStepAttack, ksys::act::ai::Ai)
public:
    explicit BocoblinBackStepAttack(const InitArg& arg);
    ~BocoblinBackStepAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    int* mAttackPer_d{};
};

}  // namespace uking::ai
