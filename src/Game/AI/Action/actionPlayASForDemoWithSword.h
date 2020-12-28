#pragma once

#include "Game/AI/Action/actionPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayASForDemoWithSword : public PlayASForDemo {
    SEAD_RTTI_OVERRIDE(PlayASForDemoWithSword, PlayASForDemo)
public:
    explicit PlayASForDemoWithSword(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xb0
    bool* mIsHold_d{};
};

}  // namespace uking::action
