#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SunazarashiReturn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SunazarashiReturn, ksys::act::ai::Ai)
public:
    explicit SunazarashiReturn(const InitArg& arg);
    ~SunazarashiReturn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsForceReturnHome_s{};
    // aitree_variable at offset 0x40
    sead::Vector3f* mSunazarashiReturnPos_a{};
};

}  // namespace uking::ai
