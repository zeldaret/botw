#pragma once

#include "Game/AI/Action/actionSmallDamage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageDirectPreTargetBone : public SmallDamage {
    SEAD_RTTI_OVERRIDE(SmallDamageDirectPreTargetBone, SmallDamage)
public:
    explicit SmallDamageDirectPreTargetBone(const InitArg& arg);
    ~SmallDamageDirectPreTargetBone() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const int* mPreTargetBone_s{};
    // static_param at offset 0x98
    sead::SafeString mASName_s{};
    // static_param at offset 0xa8
    const bool* mIsSetHitPosSelecter_s{};
};

}  // namespace uking::action
