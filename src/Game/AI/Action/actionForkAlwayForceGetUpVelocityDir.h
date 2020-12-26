#pragma once

#include "Game/AI/Action/actionForkAlwaysForceGetUp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwayForceGetUpVelocityDir : public ForkAlwaysForceGetUp {
    SEAD_RTTI_OVERRIDE(ForkAlwayForceGetUpVelocityDir, ForkAlwaysForceGetUp)
public:
    explicit ForkAlwayForceGetUpVelocityDir(const InitArg& arg);
    ~ForkAlwayForceGetUpVelocityDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
