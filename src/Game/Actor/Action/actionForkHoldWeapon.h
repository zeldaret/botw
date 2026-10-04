#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkHoldWeapon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkHoldWeapon, ksys::act::ai::Action)
public:
    explicit ForkHoldWeapon(const InitArg& arg);
    ~ForkHoldWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const int* mSeqBank_s{};
    // static_param at offset 0x30
    const int* mTargetBone_s{};
};

}  // namespace uking::action
