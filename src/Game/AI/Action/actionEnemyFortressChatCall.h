#pragma once

#include "Game/AI/Action/actionEnemyFortressChatTalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatCall : public EnemyFortressChatTalk {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatCall, EnemyFortressChatTalk)
public:
    explicit EnemyFortressChatCall(const InitArg& arg);
    ~EnemyFortressChatCall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
