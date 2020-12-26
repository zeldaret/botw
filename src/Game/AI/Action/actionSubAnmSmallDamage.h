#pragma once

#include "Game/AI/Action/actionSmallDamage.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SubAnmSmallDamage : public SmallDamage {
    SEAD_RTTI_OVERRIDE(SubAnmSmallDamage, SmallDamage)
public:
    explicit SubAnmSmallDamage(const InitArg& arg);
    ~SubAnmSmallDamage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mSubASSlot_s{};
    // static_param at offset 0x98
    sead::SafeString mSubAS_s{};
    // static_param at offset 0xa8
    sead::SafeString mLeaveSubAS_s{};
};

}  // namespace uking::action
