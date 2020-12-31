#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReflectableThrown : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReflectableThrown, ksys::act::ai::Ai)
public:
    explicit ReflectableThrown(const InitArg& arg);
    ~ReflectableThrown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsReflectByGuard_s{};
    // static_param at offset 0x40
    const bool* mIsReflectByArrow_s{};
    // static_param at offset 0x48
    sead::SafeString mHitColName_s{};
    // static_param at offset 0x58
    const float* mRefSpeedRatioByJustGuard_s{};
};

}  // namespace uking::ai
