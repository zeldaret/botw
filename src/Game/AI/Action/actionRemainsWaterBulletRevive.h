#pragma once

#include "Game/AI/Action/actionRemainsWaterBulletWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterBulletRevive : public RemainsWaterBulletWait {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletRevive, RemainsWaterBulletWait)
public:
    explicit RemainsWaterBulletRevive(const InitArg& arg);
    ~RemainsWaterBulletRevive() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    sead::SafeString mXLinkKey_s{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
