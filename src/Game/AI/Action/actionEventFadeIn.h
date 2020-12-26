#pragma once

#include "Game/AI/Action/actionEventFade.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventFadeIn : public EventFade {
    SEAD_RTTI_OVERRIDE(EventFadeIn, EventFade)
public:
    explicit EventFadeIn(const InitArg& arg);
    ~EventFadeIn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
