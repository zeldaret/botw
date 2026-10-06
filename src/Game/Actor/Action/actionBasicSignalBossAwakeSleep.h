#pragma once

#include "Game/Actor/Action/actionBasicSignalEnemyNotice.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalBossAwakeSleep : public BasicSignalEnemyNotice {
    SEAD_RTTI_OVERRIDE(BasicSignalBossAwakeSleep, BasicSignalEnemyNotice)
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
