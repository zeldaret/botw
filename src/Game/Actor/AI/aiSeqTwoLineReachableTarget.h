#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTwoLineReachableTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqTwoLineReachableTarget, ksys::act::ai::Ai)
public:
    explicit SeqTwoLineReachableTarget(const InitArg& arg);
    ~SeqTwoLineReachableTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mReachableCheckType1_s{};
    // static_param at offset 0x40
    const int* mReachableCheckType2_s{};
};

}  // namespace uking::ai
