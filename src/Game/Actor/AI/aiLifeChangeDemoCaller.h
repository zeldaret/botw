#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LifeChangeDemoCaller : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LifeChangeDemoCaller, ksys::act::ai::Ai)
public:
    explicit LifeChangeDemoCaller(const InitArg& arg);
    ~LifeChangeDemoCaller() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLifeRatio_s{};
    // static_param at offset 0x40
    const bool* mOnlyOnce_s{};
    // static_param at offset 0x48
    const bool* mIsIgnorePlayerLand_s{};
    // static_param at offset 0x50
    sead::SafeString mDemoName_s{};
    // static_param at offset 0x60
    sead::SafeString mDemoEntryPoint_s{};
};

}  // namespace uking::ai
