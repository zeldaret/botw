#pragma once

#include "Game/AI/Action/actionAnimalFollowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseFollow : public AnimalFollowBase {
    SEAD_RTTI_OVERRIDE(HorseFollow, AnimalFollowBase)
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
