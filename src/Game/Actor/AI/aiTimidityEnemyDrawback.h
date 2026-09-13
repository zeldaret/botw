#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TimidityEnemyDrawback : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TimidityEnemyDrawback, ksys::act::ai::Ai)
public:
    explicit TimidityEnemyDrawback(const InitArg& arg);
    ~TimidityEnemyDrawback() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mEscapeDist_s{};
    // static_param at offset 0x40
    const float* mEscapeDistFromHome_s{};
    // static_param at offset 0x48
    const float* mLostRange_s{};
    // static_param at offset 0x50
    const float* mLostVMin_s{};
    // static_param at offset 0x58
    const float* mLostVMax_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
