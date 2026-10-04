#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyFindShootable : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyFindShootable, ksys::act::ai::Ai)
public:
    explicit EnemyFindShootable(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mGrabCheckRadius_s{};
    // static_param at offset 0x40
    const bool* mCanGrabHeavy_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mAttOffset_s{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcLink* mTargetActor_d{};
    // static_param at offset 0x58
    const float* mChaseItemDist_s{};
    // static_param at offset 0x60
    const float* mChaseItemSpeed_s{};
};

}  // namespace uking::ai
