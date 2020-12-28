#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoldArrow : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(HoldArrow, ActionWithPosAngReduce)
public:
    explicit HoldArrow(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
