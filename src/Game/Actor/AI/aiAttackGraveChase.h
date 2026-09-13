#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AttackGraveChase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AttackGraveChase, ksys::act::ai::Ai)
public:
    explicit AttackGraveChase(const InitArg& arg);
    ~AttackGraveChase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mActionTime_s{};
    // static_param at offset 0x40
    const int* mNearTime_s{};
    // static_param at offset 0x48
    const float* mEndHeight_s{};
    // static_param at offset 0x50
    const float* mEndNear_s{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
