#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemyNoHeadWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyNoHeadWait, ksys::act::ai::Ai)
public:
    explicit StalEnemyNoHeadWait(const InitArg& arg);
    ~StalEnemyNoHeadWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRebootDistance_s{};
    // static_param at offset 0x40
    const float* mRebootTimer_s{};
    // dynamic_param at offset 0x48
    bool* mIsExistLivingHead_d{};
    // dynamic_param at offset 0x50
    bool* mIsExistActiveActor_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
