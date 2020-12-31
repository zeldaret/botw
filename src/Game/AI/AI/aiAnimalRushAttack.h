#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRushAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRushAttack, ksys::act::ai::Ai)
public:
    explicit AnimalRushAttack(const InitArg& arg);
    ~AnimalRushAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mUpdateTargetPosTime_s{};
    // static_param at offset 0x40
    const float* mAttackPosOffsetLength_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
