#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBlownOff : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniBlownOff, ksys::act::ai::Ai)
public:
    explicit GuardianMiniBlownOff(const InitArg& arg);
    ~GuardianMiniBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRotNeckAngle_s{};
    // static_param at offset 0x40
    const float* mRotNeckSpeed_s{};
};

}  // namespace uking::ai
