#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormNoticeSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormNoticeSound, ksys::act::ai::Ai)
public:
    explicit SandwormNoticeSound(const InitArg& arg);
    ~SandwormNoticeSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRetryDist_s{};
    // static_param at offset 0x40
    const float* mTargetActorLockOnDist_s{};
    // static_param at offset 0x48
    const float* mTargetPosLockOnDist_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
