#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Catch : public ActionEx {
    SEAD_RTTI_OVERRIDE(Catch, ActionEx)
public:
    explicit Catch(const InitArg& arg);
    ~Catch() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mWeaponIdx_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // dynamic_param at offset 0x30
    ksys::act::BaseProcLink* mTargetWeapon_d{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
