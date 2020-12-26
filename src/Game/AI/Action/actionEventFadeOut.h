#pragma once

#include "Game/AI/Action/actionEventFade.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventFadeOut : public EventFade {
    SEAD_RTTI_OVERRIDE(EventFadeOut, EventFade)
public:
    explicit EventFadeOut(const InitArg& arg);
    ~EventFadeOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
