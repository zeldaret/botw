#pragma once

#include "Game/AI/AI/aiWillBallFollowAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WillBallFollowAttackWithDynAng : public WillBallFollowAttack {
    SEAD_RTTI_OVERRIDE(WillBallFollowAttackWithDynAng, WillBallFollowAttack)
public:
    explicit WillBallFollowAttackWithDynAng(const InitArg& arg);
    ~WillBallFollowAttackWithDynAng() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x90
    sead::Vector3f* mAngle_d{};
};

}  // namespace uking::ai
