#pragma once

#include "Game/AI/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniViewWait : public ViewWait {
    SEAD_RTTI_OVERRIDE(GuardianMiniViewWait, ViewWait)
public:
    explicit GuardianMiniViewWait(const InitArg& arg);
    ~GuardianMiniViewWait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const int* mASSlotRight_s{};
    // static_param at offset 0x68
    const int* mASSlotLeft_s{};
    // static_param at offset 0x70
    const int* mASSlotBack_s{};
    // static_param at offset 0x78
    sead::SafeString mRootNodeName_s{};
    // static_param at offset 0x88
    sead::SafeString mArm1NodeName_s{};
    // static_param at offset 0x98
    sead::SafeString mArm2NodeName_s{};
    // static_param at offset 0xa8
    sead::SafeString mArm3NodeName_s{};
    // static_param at offset 0xb8
    const bool* mIsPartialBind_s{};
};

}  // namespace uking::ai
