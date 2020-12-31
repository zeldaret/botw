#pragma once

#include "Game/AI/AI/aiTargetBeatCheck.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetBeatGetDrop : public TargetBeatCheck {
    SEAD_RTTI_OVERRIDE(TargetBeatGetDrop, TargetBeatCheck)
public:
    explicit TargetBeatGetDrop(const InitArg& arg);
    ~TargetBeatGetDrop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSearchDist_s{};
};

}  // namespace uking::ai
