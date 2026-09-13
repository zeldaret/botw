#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeaponRootAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeaponRootAI, ksys::act::ai::Ai)
public:
    explicit WeaponRootAI(const InitArg& arg);
    ~WeaponRootAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x48];
    // static_param at offset 0x80
    const float* mBlinkFrame_s{};
    // static_param at offset 0x88
    const float* mFallOutSpeed_s{};
    // static_param at offset 0x90
    const float* mLandNoiseLevel_s{};
    // map_unit_param at offset 0x98
    const bool* mIsFixedPlace_m{};
    // map_unit_param at offset 0xa0
    const bool* mIsEmitLandNoise_m{};
};

}  // namespace uking::ai
