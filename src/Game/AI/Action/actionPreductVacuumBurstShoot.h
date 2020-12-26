#pragma once

#include "Game/AI/Action/actionHoverPredictVacuumShoot.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PreductVacuumBurstShoot : public HoverPredictVacuumShoot {
    SEAD_RTTI_OVERRIDE(PreductVacuumBurstShoot, HoverPredictVacuumShoot)
public:
    explicit PreductVacuumBurstShoot(const InitArg& arg);
    ~PreductVacuumBurstShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    const float* mBulletOffset_s{};
    // static_param at offset 0x140
    sead::SafeString mPartsKey2_s{};
    // static_param at offset 0x150
    sead::SafeString mPartsKey3_s{};
};

}  // namespace uking::action
