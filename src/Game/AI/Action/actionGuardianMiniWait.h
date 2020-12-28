#pragma once

#include "Game/AI/Action/actionWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniWait : public Wait {
    SEAD_RTTI_OVERRIDE(GuardianMiniWait, Wait)
public:
    explicit GuardianMiniWait(const InitArg& arg);
    ~GuardianMiniWait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    // static_param at offset 0x60
    const int* mASSlotRight_s{};
    // static_param at offset 0x68
    const int* mASSlotLeft_s{};
    // static_param at offset 0x70
    const int* mASSlotBack_s{};
    // dynamic_param at offset 0x78
    int* mDynRightWeaponIdx_d{};
    // dynamic_param at offset 0x80
    int* mDynLeftWeaponIdx_d{};
    // dynamic_param at offset 0x88
    int* mDynBackWeaponIdx_d{};
};

}  // namespace uking::action
