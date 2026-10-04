#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniChangeWeapon : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniChangeWeapon, ksys::act::ai::Ai)
public:
    explicit GuardianMiniChangeWeapon(const InitArg& arg);
    ~GuardianMiniChangeWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRotValue_s{};
    // static_param at offset 0x40
    const float* mRotSpeed_s{};
    // static_param at offset 0x48
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x58
    sead::SafeString mDamageNodeName_s{};
    // static_param at offset 0x68
    sead::SafeString mDamageASName_s{};
};

}  // namespace uking::ai
