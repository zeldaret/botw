#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCTalkBalloon : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCTalkBalloon, ksys::act::ai::Ai)
public:
    explicit NPCTalkBalloon(const InitArg& arg);
    ~NPCTalkBalloon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDurationTime_s{};
    // static_param at offset 0x40
    const int* mDelayFrame_s{};
    // dynamic_param at offset 0x48
    sead::SafeString* mMessageId_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
