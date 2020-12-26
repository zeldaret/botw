#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnetimeChangeableASPlay : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(OnetimeChangeableASPlay, OnetimeStopASPlay)
public:
    explicit OnetimeChangeableASPlay(const InitArg& arg);
    ~OnetimeChangeableASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
