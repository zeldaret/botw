#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CliffCheckSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CliffCheckSelect, ksys::act::ai::Ai)
public:
    explicit CliffCheckSelect(const InitArg& arg);
    ~CliffCheckSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCheckDist_s{};
    // static_param at offset 0x40
    const float* mCheckAngle_s{};
    // static_param at offset 0x48
    const bool* mIsSelectFirstTime_s{};
};

}  // namespace uking::ai
