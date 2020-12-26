#pragma once

#include "Game/AI/Action/actionAnimalFollowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalFollow : public AnimalFollowBase {
    SEAD_RTTI_OVERRIDE(AnimalFollow, AnimalFollowBase)
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
