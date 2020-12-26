#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardJust : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(GuardJust, OnetimeStopASPlay)
public:
    explicit GuardJust(const InitArg& arg);
    ~GuardJust() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
