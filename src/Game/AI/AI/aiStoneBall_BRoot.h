#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneBall_BRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneBall_BRoot, ksys::act::ai::Ai)
public:
    explicit StoneBall_BRoot(const InitArg& arg);
    ~StoneBall_BRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mWeaponImpulseAmplifyPower_s{};
    // static_param at offset 0x40
    const float* mBombImpulseAmplifyPower_s{};
    // static_param at offset 0x48
    const float* mDoubleBombImpulseAmplifyPower_s{};
};

}  // namespace uking::ai
