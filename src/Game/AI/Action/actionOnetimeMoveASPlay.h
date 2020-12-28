#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnetimeMoveASPlay : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(OnetimeMoveASPlay, OnetimeStopASPlay)
public:
    explicit OnetimeMoveASPlay(const InitArg& arg);
    ~OnetimeMoveASPlay() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const bool* mIsChangable_s{};
};

}  // namespace uking::action
