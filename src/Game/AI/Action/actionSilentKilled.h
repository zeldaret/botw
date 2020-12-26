#pragma once

#include "Game/AI/Action/actionRagdoll.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SilentKilled : public Ragdoll {
    SEAD_RTTI_OVERRIDE(SilentKilled, Ragdoll)
public:
    explicit SilentKilled(const InitArg& arg);
    ~SilentKilled() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
