#pragma once

#include "Game/AI/Action/actionFollowChallenge.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonFollow : public FollowChallenge {
    SEAD_RTTI_OVERRIDE(DragonFollow, FollowChallenge)
public:
    explicit DragonFollow(const InitArg& arg);
    ~DragonFollow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xab0
    sead::SafeString mDungeonName_s{};
};

}  // namespace uking::action
