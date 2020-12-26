#pragma once

#include "Game/AI/Action/actionSiteBossSpearAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSpearAttackVertical : public SiteBossSpearAttackBase {
    SEAD_RTTI_OVERRIDE(SiteBossSpearAttackVertical, SiteBossSpearAttackBase)
public:
    explicit SiteBossSpearAttackVertical(const InitArg& arg);
    ~SiteBossSpearAttackVertical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x100
    const int* mShockWaveAttackPower_s{};
};

}  // namespace uking::action
