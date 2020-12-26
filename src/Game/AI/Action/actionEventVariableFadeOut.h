#pragma once

#include "Game/AI/Action/actionEventVariableFade.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventVariableFadeOut : public EventVariableFade {
    SEAD_RTTI_OVERRIDE(EventVariableFadeOut, EventVariableFade)
public:
    explicit EventVariableFadeOut(const InitArg& arg);
    ~EventVariableFadeOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
