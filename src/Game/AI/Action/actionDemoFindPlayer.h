#pragma once

#include "Game/AI/Action/actionTimeredASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoFindPlayer : public TimeredASPlay {
    SEAD_RTTI_OVERRIDE(DemoFindPlayer, TimeredASPlay)
public:
    explicit DemoFindPlayer(const InitArg& arg);
    ~DemoFindPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
