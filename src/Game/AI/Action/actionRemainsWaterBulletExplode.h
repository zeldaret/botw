#pragma once

#include "Game/AI/Action/actionExplode.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterBulletExplode : public Explode {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletExplode, Explode)
public:
    explicit RemainsWaterBulletExplode(const InitArg& arg);
    ~RemainsWaterBulletExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x80
    const int* mMaxDamage_s{};
    // static_param at offset 0x88
    const int* mMinDamage_s{};
};

}  // namespace uking::action
