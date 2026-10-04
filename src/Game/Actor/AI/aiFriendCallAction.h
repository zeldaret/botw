#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FriendCallAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FriendCallAction, ksys::act::ai::Ai)
public:
    explicit FriendCallAction(const InitArg& arg);
    ~FriendCallAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mNearDistH_s{};
    // static_param at offset 0x48
    const float* mNearDistVMax_s{};
    // static_param at offset 0x50
    const float* mNearDistVMin_s{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
