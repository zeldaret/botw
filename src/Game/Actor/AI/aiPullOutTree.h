#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PullOutTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PullOutTree, ksys::act::ai::Ai)
public:
    explicit PullOutTree(const InitArg& arg);
    ~PullOutTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnAng_s{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
