#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaitAndFaceLeader : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaitAndFaceLeader, ksys::act::ai::Ai)
public:
    explicit WaitAndFaceLeader(const InitArg& arg);
    ~WaitAndFaceLeader() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnThreshold_s{};
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mLeaderActor_d{};
};

}  // namespace uking::ai
