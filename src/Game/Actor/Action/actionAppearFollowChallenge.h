#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearFollowChallenge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearFollowChallenge, ksys::act::ai::Action)
public:
    explicit AppearFollowChallenge(const InitArg& arg);
    ~AppearFollowChallenge() override;

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
