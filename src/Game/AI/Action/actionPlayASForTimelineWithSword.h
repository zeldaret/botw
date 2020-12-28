#pragma once

#include "Game/AI/Action/actionPlayASForTimeline.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayASForTimelineWithSword : public PlayASForTimeline {
    SEAD_RTTI_OVERRIDE(PlayASForTimelineWithSword, PlayASForTimeline)
public:
    explicit PlayASForTimelineWithSword(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xb8
    bool* mIsHold_d{};
};

}  // namespace uking::action
