#pragma once

#include "Game/AI/AI/aiTimeredViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewWaitEndWhenAimed : public TimeredViewWait {
    SEAD_RTTI_OVERRIDE(ViewWaitEndWhenAimed, TimeredViewWait)
public:
    explicit ViewWaitEndWhenAimed(const InitArg& arg);
    ~ViewWaitEndWhenAimed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x78
    const int* mEndTime_s{};
    // static_param at offset 0x80
    const float* mAimedAngle_s{};
    // static_param at offset 0x88
    const float* mBowRange_s{};
    // static_param at offset 0x90
    sead::SafeString mBoneName_s{};
};

}  // namespace uking::ai
