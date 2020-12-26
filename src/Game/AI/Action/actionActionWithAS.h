#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ActionWithAS : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(ActionWithAS, ActionWithPosAngReduce)
public:
    explicit ActionWithAS(const InitArg& arg);
    ~ActionWithAS() override;

    bool init_(sead::Heap* heap) override;
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
