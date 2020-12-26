#pragma once

#include "Game/AI/Action/actionBasicSignalEnemy.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalBossAwakeSleep : public BasicSignalEnemy {
    SEAD_RTTI_OVERRIDE(BasicSignalBossAwakeSleep, BasicSignalEnemy)
public:
    explicit BasicSignalBossAwakeSleep(const InitArg& arg);
    ~BasicSignalBossAwakeSleep() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
