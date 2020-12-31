#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TrolleyOnRail : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TrolleyOnRail, ksys::act::ai::Ai)
public:
    explicit TrolleyOnRail(const InitArg& arg);
    ~TrolleyOnRail() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    float* mRailDist_d{};
    // dynamic_param at offset 0x40
    float* mVelocityReduce_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mRailPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mRailDir_d{};
};

}  // namespace uking::ai
