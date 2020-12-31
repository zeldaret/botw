#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelDirSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelDirSelect, ksys::act::ai::Ai)
public:
    explicit LynelDirSelect(const InitArg& arg);
    ~LynelDirSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBasePosOffsetFront_s{};
    // static_param at offset 0x40
    const float* mBasePosOffsetBack_s{};
    // static_param at offset 0x48
    const float* mFrontAngle_s{};
    // static_param at offset 0x50
    const float* mBackAngle_s{};
    // static_param at offset 0x58
    const bool* mIsCheckOnlyXZ_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
