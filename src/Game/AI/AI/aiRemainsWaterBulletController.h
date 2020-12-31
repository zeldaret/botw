#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterBulletController : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletController, ksys::act::ai::Ai)
public:
    explicit RemainsWaterBulletController(const InitArg& arg);
    ~RemainsWaterBulletController() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x18];
    // static_param at offset 0x50
    const float* mInsideAreaRadius_s{};
    // static_param at offset 0x58
    const float* mFirstBulletTimer_s{};
    // static_param at offset 0x60
    const float* mSecondBulletTimer_s{};
    // static_param at offset 0x68
    const float* mNextBulletTimerSuccess_s{};
    // static_param at offset 0x70
    const float* mNextBulletTimerFail_s{};
    // static_param at offset 0x78
    sead::SafeString mChaseBulletNum_s{};
    // static_param at offset 0x88
    sead::SafeString mExplodeBulletNum_s{};
    // static_param at offset 0x98
    sead::SafeString mChaseBulletActorName_s{};
    // static_param at offset 0xa8
    sead::SafeString mExplodeBulletActorName_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mInsideAreaCenter_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mInsideAreaWidth_s{};
    // aitree_variable at offset 0xc8
    void* mRemainsWaterBattleInfo_a{};
};

}  // namespace uking::ai
