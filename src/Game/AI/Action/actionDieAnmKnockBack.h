#pragma once

#include "Game/AI/Action/actionSmallDamageBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DieAnmKnockBack : public SmallDamageBase {
    SEAD_RTTI_OVERRIDE(DieAnmKnockBack, SmallDamageBase)
public:
    explicit DieAnmKnockBack(const InitArg& arg);
    ~DieAnmKnockBack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const float* mWeaponDropSpeedY_s{};
    // static_param at offset 0x98
    const bool* mIsDropWeapon_s{};
    // static_param at offset 0xa0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
