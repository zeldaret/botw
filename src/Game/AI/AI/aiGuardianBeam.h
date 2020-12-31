#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianBeam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianBeam, ksys::act::ai::Ai)
public:
    explicit GuardianBeam(const InitArg& arg);
    ~GuardianBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mMaxDistance_s{};
};

}  // namespace uking::ai
