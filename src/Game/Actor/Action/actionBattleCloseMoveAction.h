#pragma once

#include "Game/Actor/Action/actionAvoidingCloseMoveActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMoveAction : public AvoidingCloseMoveActionBase {
    SEAD_RTTI_OVERRIDE(BattleCloseMoveAction, AvoidingCloseMoveActionBase)
public:
    explicit BattleCloseMoveAction(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
