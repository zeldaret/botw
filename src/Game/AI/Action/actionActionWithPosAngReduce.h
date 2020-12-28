#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActionWithPosAngReduce : public ActionEx {
    SEAD_RTTI_OVERRIDE(ActionWithPosAngReduce, ActionEx)
public:
    explicit ActionWithPosAngReduce(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mAngReduceRatio_s{};
};

}  // namespace uking::action
