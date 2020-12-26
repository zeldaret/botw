#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowChallenge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FollowChallenge, ksys::act::ai::Action)
public:
    explicit FollowChallenge(const InitArg& arg);
    ~FollowChallenge() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const float* mGimmickTimeLimit_m{};
    // map_unit_param at offset 0x28
    const bool* mIsBillboard_m{};
};

}  // namespace uking::action
