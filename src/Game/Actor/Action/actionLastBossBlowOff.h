#pragma once

#include "Game/Actor/Action/actionBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossBlowOff : public BlownOff {
    SEAD_RTTI_OVERRIDE(LastBossBlowOff, BlownOff)
public:
    explicit LastBossBlowOff(const InitArg& arg);
    ~LastBossBlowOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
