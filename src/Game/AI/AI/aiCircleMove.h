#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CircleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CircleMove, ksys::act::ai::Ai)
public:
    explicit CircleMove(const InitArg& arg);
    ~CircleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDirection_s{};
    // static_param at offset 0x40
    const float* mRadius_s{};
    // static_param at offset 0x48
    const float* mRadiusMargin_s{};
    // static_param at offset 0x50
    const float* mSpeed_s{};
};

}  // namespace uking::ai
