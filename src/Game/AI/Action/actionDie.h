#pragma once

#include "Game/AI/Action/actionBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Die : public BlownOff {
    SEAD_RTTI_OVERRIDE(Die, BlownOff)
public:
    explicit Die(const InitArg& arg);
    ~Die() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
