#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RestartStageFromGameOver : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RestartStageFromGameOver, ksys::act::ai::Action)
public:
    explicit RestartStageFromGameOver(const InitArg& arg);
    ~RestartStageFromGameOver() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
