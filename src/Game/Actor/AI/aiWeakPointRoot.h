#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeakPointRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeakPointRoot, ksys::act::ai::Ai)
public:
    explicit WeakPointRoot(const InitArg& arg);
    ~WeakPointRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mOwnerDamage_s{};
    // static_param at offset 0x40
    const bool* mIsBreakable_s{};
    // static_param at offset 0x48
    const bool* mIsSyncDamage_s{};
    // static_param at offset 0x50
    const bool* mIsShowCriticalEffect_s{};
    // static_param at offset 0x58
    const bool* mIsNoReaction_s{};
};

}  // namespace uking::ai
