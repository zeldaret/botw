#pragma once

#include "Game/Actor/AI/aiSleepNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemySleep : public SleepNormal {
    SEAD_RTTI_OVERRIDE(StalEnemySleep, SleepNormal)
public:
    explicit StalEnemySleep(const InitArg& arg);
    ~StalEnemySleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const bool* mUseAwarenessWakeUp_s{};
    // static_param at offset 0x68
    const bool* mUseNoticeActiveWakeUp_s{};
};

}  // namespace uking::ai
