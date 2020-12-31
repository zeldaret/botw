#pragma once

#include "Game/AI/AI/aiWaitForTargetClose.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WaitForCloseOrWaterSide : public WaitForTargetClose {
    SEAD_RTTI_OVERRIDE(WaitForCloseOrWaterSide, WaitForTargetClose)
public:
    explicit WaitForCloseOrWaterSide(const InitArg& arg);
    ~WaitForCloseOrWaterSide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x58
    const float* mDistFromWater_s{};
};

}  // namespace uking::ai
