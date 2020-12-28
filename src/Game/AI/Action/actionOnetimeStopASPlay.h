#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnetimeStopASPlay : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(OnetimeStopASPlay, ActionWithAS)
public:
    explicit OnetimeStopASPlay(const InitArg& arg);
    ~OnetimeStopASPlay() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
