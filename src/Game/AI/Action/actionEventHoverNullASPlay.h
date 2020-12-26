#pragma once

#include "Game/AI/Action/actionEventHoverNullASPlayBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventHoverNullASPlay : public EventHoverNullASPlayBase {
    SEAD_RTTI_OVERRIDE(EventHoverNullASPlay, EventHoverNullASPlayBase)
public:
    explicit EventHoverNullASPlay(const InitArg& arg);
    ~EventHoverNullASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
