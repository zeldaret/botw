#pragma once

#include "Game/AI/AI/aiTargetActorGrabAdapter.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleDlcGrabAdapter : public TargetActorGrabAdapter {
    SEAD_RTTI_OVERRIDE(AssassinMiddleDlcGrabAdapter, TargetActorGrabAdapter)
public:
    explicit AssassinMiddleDlcGrabAdapter(const InitArg& arg);
    ~AssassinMiddleDlcGrabAdapter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
