#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonTurn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DragonTurn, ksys::act::ai::Ai)
public:
    explicit DragonTurn(const InitArg& arg);
    ~DragonTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mAvoidStartDistance_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetVec_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
