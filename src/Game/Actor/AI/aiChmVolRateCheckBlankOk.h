#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChmVolRateCheckBlankOk : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChmVolRateCheckBlankOk, ksys::act::ai::Ai)
public:
    explicit ChmVolRateCheckBlankOk(const InitArg& arg);
    ~ChmVolRateCheckBlankOk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mVolTh_s{};
    // static_param at offset 0x40
    const float* mDebugScale_s{};
    // static_param at offset 0x48
    const bool* mDebugDraw_s{};
    // static_param at offset 0x50
    const bool* mIsInvalidBreakJudge_s{};
    // map_unit_param at offset 0x58
    const int* mFreezeTarget_m{};
    // map_unit_param at offset 0x60
    const float* mIceBreakScale_m{};
};

}  // namespace uking::ai
