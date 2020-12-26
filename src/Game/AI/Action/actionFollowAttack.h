#pragma once

#include "Game/AI/Action/actionRotateTurnToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FollowAttack : public RotateTurnToTarget {
    SEAD_RTTI_OVERRIDE(FollowAttack, RotateTurnToTarget)
public:
    explicit FollowAttack(const InitArg& arg);
    ~FollowAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x108
    const bool* mForceKillMode_s{};
    // static_param at offset 0x110
    const bool* mIsRodDirHosei_s{};
};

}  // namespace uking::action
