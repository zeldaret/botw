#pragma once

#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GiantSleepNormal : public SpecialEnemySleep {
    SEAD_RTTI_OVERRIDE(GiantSleepNormal, SpecialEnemySleep)
public:
    explicit GiantSleepNormal(const InitArg& arg);
    ~GiantSleepNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const float* mForceAwakeDist_s{};
    // static_param at offset 0x68
    sead::SafeString mAwakeRbName_s{};
};

}  // namespace uking::ai
