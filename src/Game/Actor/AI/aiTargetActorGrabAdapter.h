#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetActorGrabAdapter : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetActorGrabAdapter, ksys::act::ai::Ai)
public:
    explicit TargetActorGrabAdapter(const InitArg& arg);
    ~TargetActorGrabAdapter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
