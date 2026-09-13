#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterBulletShooter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletShooter, ksys::act::ai::Action)
public:
    explicit RemainsWaterBulletShooter(const InitArg& arg);
    ~RemainsWaterBulletShooter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mBulletType_s{};
    // static_param at offset 0x28
    const int* mReloadCounter_s{};
    // static_param at offset 0x30
    const float* mOffsetAngle_s{};
    // static_param at offset 0x38
    const bool* mUseRandRot_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x48
    const sead::Vector3f* mBaseShootParam_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mOffsetYParam_s{};
    // aitree_variable at offset 0x58
    void* mRemainsWaterBattleInfo_a{};
};

}  // namespace uking::action
