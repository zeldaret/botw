#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WeaponTrueFormEftCtrl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WeaponTrueFormEftCtrl, ksys::act::ai::Action)
public:
    explicit WeaponTrueFormEftCtrl(const InitArg& arg);
    ~WeaponTrueFormEftCtrl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mTransformKey_s{};
    // static_param at offset 0x30
    sead::SafeString mTrueFormKey_s{};
};

}  // namespace uking::action
