#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonReturn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DragonReturn, ksys::act::ai::Ai)
public:
    explicit DragonReturn(const InitArg& arg);
    ~DragonReturn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSpeed_s{};
    // static_param at offset 0x40
    const float* mRotateRate_s{};
    // static_param at offset 0x48
    const float* mChangeMoveHeight_s{};
    // static_param at offset 0x50
    const float* mFinishHeight_s{};
    // static_param at offset 0x58
    const float* mAngle_s{};
    // static_param at offset 0x60
    const float* mAvoidStartDistance_s{};
    // static_param at offset 0x68
    const float* mReturnStartFrame_s{};
};

}  // namespace uking::ai
