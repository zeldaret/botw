#pragma once

#include "Game/AI/AI/aiAnimalTimelineAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KakarikoKokkoTimeline : public AnimalTimelineAI {
    SEAD_RTTI_OVERRIDE(KakarikoKokkoTimeline, AnimalTimelineAI)
public:
    explicit KakarikoKokkoTimeline(const InitArg& arg);
    ~KakarikoKokkoTimeline() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    sead::SafeString mForceChangeChildKeyName_s{};
    // static_param at offset 0x90
    sead::SafeString mStartForceChangeFlagName_s{};
    // static_param at offset 0xa0
    sead::SafeString mEndForceChangeFlagName_s{};
    // map_unit_param at offset 0xb0
    sead::SafeString mCheckGatheredFlagName_m{};
};

}  // namespace uking::ai
