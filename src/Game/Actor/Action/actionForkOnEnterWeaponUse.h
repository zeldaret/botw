#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkOnEnterWeaponUse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkOnEnterWeaponUse, ksys::act::ai::Action)
public:
    explicit ForkOnEnterWeaponUse(const InitArg& arg);
    ~ForkOnEnterWeaponUse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
