#pragma once

#include "Game/AI/Action/actionPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayASForTimeline : public PlayASForDemo {
    SEAD_RTTI_OVERRIDE(PlayASForTimeline, PlayASForDemo)
public:
    explicit PlayASForTimeline(const InitArg& arg);
    ~PlayASForTimeline() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xb0
    int* mClipIndex_d{};
};

}  // namespace uking::action
