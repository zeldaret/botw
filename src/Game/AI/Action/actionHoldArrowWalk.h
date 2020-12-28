#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoldArrowWalk : public MoveBase {
    SEAD_RTTI_OVERRIDE(HoldArrowWalk, MoveBase)
public:
    explicit HoldArrowWalk(const InitArg& arg);
    ~HoldArrowWalk() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe0
    const int* mHoldWeaponIdx_s{};
};

}  // namespace uking::action
