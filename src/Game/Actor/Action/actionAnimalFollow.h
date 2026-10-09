#pragma once

#include "Game/Actor/Action/actionHorseFollowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalFollow : public HorseFollowBase {
    SEAD_RTTI_OVERRIDE(AnimalFollow, HorseFollowBase)
public:
    explicit AnimalFollow(const InitArg& arg);
    ~AnimalFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const float* mDistanceKept_s{};
};

}  // namespace uking::action
