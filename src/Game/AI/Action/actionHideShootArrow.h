#pragma once

#include "Game/AI/Action/actionShootArrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HideShootArrow : public ShootArrow {
    SEAD_RTTI_OVERRIDE(HideShootArrow, ShootArrow)
public:
    explicit HideShootArrow(const InitArg& arg);
    ~HideShootArrow() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    sead::SafeString mShootStartASName_s{};
    // static_param at offset 0xc0
    sead::SafeString mShootASName_s{};
    // static_param at offset 0xd0
    sead::SafeString mShootEndASName_s{};
    // static_param at offset 0xe0
    const int* mLoopTime_s{};
};

}  // namespace uking::action
