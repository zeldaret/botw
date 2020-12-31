#pragma once

#include "Game/AI/AI/aiTimelineAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalTimelineAI : public TimelineAI {
    SEAD_RTTI_OVERRIDE(AnimalTimelineAI, TimelineAI)
public:
    explicit AnimalTimelineAI(const InitArg& arg);
    ~AnimalTimelineAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x40
    sead::SafeString* mDomesticAnimalRailName_a{};
};

}  // namespace uking::ai
