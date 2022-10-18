#pragma once

#include "Game/AI/Action/actionEventHoverNullASPlayBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

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

    void resetAllMotion(ksys::act::Actor* actor) {
        mCCAccessor.resetRigidBodyMotion(actor);
        mCCAccessor.resetMotionType(actor->getCharacterController());
    }

    ksys::act::CCAccessor mCCAccessor;
};

}  // namespace uking::action
