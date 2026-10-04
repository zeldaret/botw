#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WeakStateSelecter : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WeakStateSelecter, ksys::act::ai::Ai)
public:
    explicit WeakStateSelecter(const InitArg& arg);
    ~WeakStateSelecter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsAlwaysUpdate_s{};
    // aitree_variable at offset 0x40
    bool* mIsWeakPointAppearMode_a{};
};

}  // namespace uking::ai
