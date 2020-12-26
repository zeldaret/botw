#pragma once

#include "Game/AI/Action/actionBattleCloseSlippedWalkBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleCloseSlippedWalk : public BattleCloseSlippedWalkBase {
    SEAD_RTTI_OVERRIDE(BattleCloseSlippedWalk, BattleCloseSlippedWalkBase)
public:
    explicit BattleCloseSlippedWalk(const InitArg& arg);
    ~BattleCloseSlippedWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
