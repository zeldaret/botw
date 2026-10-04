#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetElevationGapSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetElevationGapSelect, ksys::act::ai::Ai)
public:
    explicit TargetElevationGapSelect(const InitArg& arg);
    ~TargetElevationGapSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mElvGap_s{};
};

}  // namespace uking::ai
