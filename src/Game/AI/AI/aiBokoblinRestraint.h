#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinRestraint : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinRestraint, ksys::act::ai::Ai)
public:
    explicit BokoblinRestraint(const InitArg& arg);
    ~BokoblinRestraint() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x40
    const float* mBaseDist_s{};
    // static_param at offset 0x48
    const float* mLostVMin_s{};
    // static_param at offset 0x50
    const float* mLostVMax_s{};
    // static_param at offset 0x58
    const int* mLostTimer_s{};
    // static_param at offset 0x60
    const float* mLostRange_s{};
};

}  // namespace uking::ai
