#pragma once

#include "Game/AI/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewWaitWithInstDynActor : public ViewWait {
    SEAD_RTTI_OVERRIDE(ViewWaitWithInstDynActor, ViewWait)
public:
    explicit ViewWaitWithInstDynActor(const InitArg& arg);
    ~ViewWaitWithInstDynActor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x60
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
