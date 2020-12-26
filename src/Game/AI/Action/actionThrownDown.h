#pragma once

#include "Game/AI/Action/actionRagdoll.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ThrownDown : public Ragdoll {
    SEAD_RTTI_OVERRIDE(ThrownDown, Ragdoll)
public:
    explicit ThrownDown(const InitArg& arg);
    ~ThrownDown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x118
    sead::Vector3f* mSetupSpeed_d{};
};

}  // namespace uking::action
