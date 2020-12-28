#pragma once

#include "Game/AI/Action/actionBattleLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleLevelFlyMove : public BattleLevelFlyMoveBase {
    SEAD_RTTI_OVERRIDE(BattleLevelFlyMove, BattleLevelFlyMoveBase)
public:
    explicit BattleLevelFlyMove(const InitArg& arg);
    ~BattleLevelFlyMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0xd8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
