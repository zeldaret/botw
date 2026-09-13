#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterChaseBulletRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterChaseBulletRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWaterChaseBulletRoot(const InitArg& arg);
    ~RemainsWaterChaseBulletRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x18];
    // static_param at offset 0x50
    const int* mAtkMinDamage_s{};
    // static_param at offset 0x58
    const float* mCheckPower_s{};
    // static_param at offset 0x60
    const float* mHighDamageAddSpd_s{};
    // static_param at offset 0x68
    const float* mLowDamageAddSpd_s{};
    // static_param at offset 0x70
    const float* mShootAddSpd_s{};
    // static_param at offset 0x78
    sead::SafeString mResetASName_s{};
};

}  // namespace uking::ai
