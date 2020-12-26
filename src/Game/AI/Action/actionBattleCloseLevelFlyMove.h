#pragma once

#include "Game/AI/Action/actionBattleCloseLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseLevelFlyMove : public BattleCloseLevelFlyMoveBase {
    SEAD_RTTI_OVERRIDE(BattleCloseLevelFlyMove, BattleCloseLevelFlyMoveBase)
public:
    explicit BattleCloseLevelFlyMove(const InitArg& arg);
    ~BattleCloseLevelFlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xf0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
