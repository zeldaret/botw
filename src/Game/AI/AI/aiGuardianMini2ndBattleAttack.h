#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMini2ndBattleAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMini2ndBattleAttack, ksys::act::ai::Ai)
public:
    explicit GuardianMini2ndBattleAttack(const InitArg& arg);
    ~GuardianMini2ndBattleAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mAscendingCurrentName_s{};
    // static_param at offset 0x48
    const int* mAscendingCurrentTime_s{};
    // aitree_variable at offset 0x50
    int* mGuardianMiniChanceTimeState_a{};
};

}  // namespace uking::ai
