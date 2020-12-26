#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AssassinBossIronMagicChargeShot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AssassinBossIronMagicChargeShot, ksys::act::ai::Action)
public:
    explicit AssassinBossIronMagicChargeShot(const InitArg& arg);
    ~AssassinBossIronMagicChargeShot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mIronBallNum_s{};
    // static_param at offset 0x28
    const int* mAttackType_s{};
    // static_param at offset 0x30
    const float* mLevel2AttackLifeRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mIronBallPartsName_s{};
};

}  // namespace uking::action
