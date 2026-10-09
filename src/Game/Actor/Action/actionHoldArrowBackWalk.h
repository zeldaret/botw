#pragma once

#include "Game/Actor/Action/actionNormalBackWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoldArrowBackWalk : public NormalBackWalk {
    SEAD_RTTI_OVERRIDE(HoldArrowBackWalk, NormalBackWalk)
public:
    explicit HoldArrowBackWalk(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mHoldWeaponIdx_s{};
};

}  // namespace uking::action
