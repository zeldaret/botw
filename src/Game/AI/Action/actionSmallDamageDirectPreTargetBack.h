#pragma once

#include "Game/AI/Action/actionSmallDamageDirectPreTargetBone.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageDirectPreTargetBack : public SmallDamageDirectPreTargetBone {
    SEAD_RTTI_OVERRIDE(SmallDamageDirectPreTargetBack, SmallDamageDirectPreTargetBone)
public:
    explicit SmallDamageDirectPreTargetBack(const InitArg& arg);
    ~SmallDamageDirectPreTargetBack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mPreTargetBone_s{};
    // static_param at offset 0x98
    sead::SafeString mASName_s{};
    // static_param at offset 0xa8
    const bool* mIsSetHitPosSelecter_s{};
};

}  // namespace uking::action
