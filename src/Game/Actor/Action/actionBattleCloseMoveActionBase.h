#pragma once

#include "Game/Actor/Action/actionAvoidingCloseMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseMoveActionBase : public AvoidingCloseMoveBase {
    SEAD_RTTI_OVERRIDE(BattleCloseMoveActionBase, AvoidingCloseMoveBase)
public:
    explicit BattleCloseMoveActionBase(const InitArg& arg);
    ~BattleCloseMoveActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
