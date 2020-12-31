#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ElectricBall : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(ElectricBall, SimpleLiftable)
public:
    explicit ElectricBall(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const float* mTargetVol_s{};
};

}  // namespace uking::ai
