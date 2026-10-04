#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonThrowActorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonThrowActorRoot, ksys::act::ai::Ai)
public:
    explicit GanonThrowActorRoot(const InitArg& arg);
    ~GanonThrowActorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mAttackDamage_s{};
    // static_param at offset 0x40
    const int* mAtMinDamage_s{};
    // static_param at offset 0x48
    const int* mAddAtackPower_s{};
    // static_param at offset 0x50
    const bool* mIsThrowQuick_s{};
    // static_param at offset 0x58
    const bool* mIsWaitBulletDelete_s{};
    // static_param at offset 0x60
    const bool* mIsSetSystemGroupHandler_s{};
    // static_param at offset 0x68
    const bool* mIsSendDeleteMessageAtLeave_s{};
    // static_param at offset 0x70
    sead::SafeString mThrowActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mRegisterPartsName_s{};
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mViewPos_d{};
};

}  // namespace uking::ai
