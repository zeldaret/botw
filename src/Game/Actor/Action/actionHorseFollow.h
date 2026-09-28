#pragma once

#include "Game/Actor/Action/actionHorseFollowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseFollow : public HorseFollowBase {
    SEAD_RTTI_OVERRIDE(HorseFollow, HorseFollowBase)
public:
    explicit HorseFollow(const InitArg& arg);
    ~HorseFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc0
    float* mDistanceKept_d{};
    // dynamic_param at offset 0xc8
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
