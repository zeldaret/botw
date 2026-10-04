#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqAnimalAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqAnimalAttack, ksys::act::ai::Ai)
public:
    explicit SeqAnimalAttack(const InitArg& arg);
    ~SeqAnimalAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsUseAfterAttackState_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
