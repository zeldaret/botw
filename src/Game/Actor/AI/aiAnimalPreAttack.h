#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalPreAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalPreAttack, ksys::act::ai::Ai)
public:
    explicit AnimalPreAttack(const InitArg& arg);
    ~AnimalPreAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mForceEndTime_s{};
    // static_param at offset 0x40
    const float* mKeepDistCheckLength_s{};
    // static_param at offset 0x48
    const float* mBackCliffCheckLength_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
