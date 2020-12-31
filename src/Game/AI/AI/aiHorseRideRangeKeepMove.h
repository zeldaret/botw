#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideRangeKeepMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRideRangeKeepMove, ksys::act::ai::Ai)
public:
    explicit HorseRideRangeKeepMove(const InitArg& arg);
    ~HorseRideRangeKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mOutDist_s{};
    // static_param at offset 0x40
    const float* mBaseDist_s{};
};

}  // namespace uking::ai
