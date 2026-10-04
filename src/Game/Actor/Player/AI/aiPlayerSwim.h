#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerSwim : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerSwim, ksys::act::ai::Ai)
public:
    explicit PlayerSwim(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCatchHeightL_s{};
    // static_param at offset 0x40
    const float* mCatchHeightH_s{};
    // static_param at offset 0x48
    const float* mEnableHeight_s{};
};

}  // namespace uking::ai
