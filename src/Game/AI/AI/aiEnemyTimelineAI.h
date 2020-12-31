#pragma once

#include "Game/AI/AI/aiTimelineAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyTimelineAI : public TimelineAI {
    SEAD_RTTI_OVERRIDE(EnemyTimelineAI, TimelineAI)
public:
    explicit EnemyTimelineAI(const InitArg& arg);
    ~EnemyTimelineAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x40
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
