#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReferenceNPCViewWithDynAS : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReferenceNPCViewWithDynAS, ksys::act::ai::Ai)
public:
    explicit ReferenceNPCViewWithDynAS(const InitArg& arg);
    ~ReferenceNPCViewWithDynAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // dynamic_param at offset 0x48
    sead::SafeString* mDynASKey_d{};
};

}  // namespace uking::ai
