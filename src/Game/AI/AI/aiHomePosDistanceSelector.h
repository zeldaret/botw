#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HomePosDistanceSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HomePosDistanceSelector, ksys::act::ai::Ai)
public:
    explicit HomePosDistanceSelector(const InitArg& arg);
    ~HomePosDistanceSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBoundaryDistance_s{};
};

}  // namespace uking::ai
