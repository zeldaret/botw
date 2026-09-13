#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HiddenKorokRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HiddenKorokRoot, ksys::act::ai::Ai)
public:
    explicit HiddenKorokRoot(const InitArg& arg);
    ~HiddenKorokRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mPainTalkHitSpeed_s{};
    // static_param at offset 0x40
    const float* mPainTalkDistance_s{};
    // map_unit_param at offset 0x48
    const int* mKorokEventStartWaitFrame_m{};
    // map_unit_param at offset 0x50
    const bool* mIsAppearCheck_m{};
    // map_unit_param at offset 0x58
    sead::SafeString mPlacementType_m{};
    // map_unit_param at offset 0x68
    const bool* mIsHiddenKorokLiftAppear_m{};
    // map_unit_param at offset 0x70
    const bool* mIsInvisibleKorok_m{};
};

}  // namespace uking::ai
