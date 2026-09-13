#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaitNearTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WaitNearTarget, ksys::act::ai::Ai)
public:
    explicit WaitNearTarget(const InitArg& arg);
    ~WaitNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mBaseDist_s{};
    // static_param at offset 0x48
    const float* mStartCloseDistOffset_s{};
    // static_param at offset 0x50
    const float* mOutDistOffset_s{};
    // static_param at offset 0x58
    const bool* mIsCheckLineReachableForClose_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
