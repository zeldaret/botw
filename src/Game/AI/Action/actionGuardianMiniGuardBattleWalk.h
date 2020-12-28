#pragma once

#include "Game/AI/Action/actionBattleCloseWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardBattleWalk : public BattleCloseWalk {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardBattleWalk, BattleCloseWalk)
public:
    explicit GuardianMiniGuardBattleWalk(const InitArg& arg);
    ~GuardianMiniGuardBattleWalk() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa8
    const int* mASSlot_s{};
    // static_param at offset 0xb0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
