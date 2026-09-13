#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolfBallRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolfBallRoot, ksys::act::ai::Ai)
public:
    explicit GolfBallRoot(const InitArg& arg);
    ~GolfBallRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIntSmashJudgeFrame_s{};
    // static_param at offset 0x40
    const int* mIntSmashContinueFrame_s{};
    // static_param at offset 0x48
    const float* mFloatJudgeSmash_s{};
    // static_param at offset 0x50
    const float* mFloatJudgeStop_s{};
};

}  // namespace uking::ai
