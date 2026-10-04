#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LargeCannonAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LargeCannonAttackRoot, ksys::act::ai::Ai)
public:
    explicit LargeCannonAttackRoot(const InitArg& arg);
    ~LargeCannonAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAttackWaitTime_s{};
};

}  // namespace uking::ai
