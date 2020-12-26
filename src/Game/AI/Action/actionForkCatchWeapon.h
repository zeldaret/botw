#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkCatchWeapon : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkCatchWeapon, ksys::act::ai::Action)
public:
    explicit ForkCatchWeapon(const InitArg& arg);
    ~ForkCatchWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const bool* mIsNoGrabSuccess_s{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
