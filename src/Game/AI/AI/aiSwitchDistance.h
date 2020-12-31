#pragma once

#include "Game/AI/AI/aiSwitchAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchDistance : public SwitchAI {
    SEAD_RTTI_OVERRIDE(SwitchDistance, SwitchAI)
public:
    explicit SwitchDistance(const InitArg& arg);
    ~SwitchDistance() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mOnDis_s{};
    // static_param at offset 0x40
    const float* mOffsetDis_s{};
    // static_param at offset 0x48
    const bool* mChangeSeq_s{};
};

}  // namespace uking::ai
