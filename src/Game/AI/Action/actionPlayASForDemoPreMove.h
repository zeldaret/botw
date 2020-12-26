#pragma once

#include "Game/AI/Action/actionPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayASForDemoPreMove : public PlayASForDemo {
    SEAD_RTTI_OVERRIDE(PlayASForDemoPreMove, PlayASForDemo)
public:
    explicit PlayASForDemoPreMove(const InitArg& arg);
    ~PlayASForDemoPreMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
