#pragma once

#include "Game/AI/Action/actionAssassinBossIronBallAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AssassinBossIronBallAtkWithRot : public AssassinBossIronBallAttack {
    SEAD_RTTI_OVERRIDE(AssassinBossIronBallAtkWithRot, AssassinBossIronBallAttack)
public:
    explicit AssassinBossIronBallAtkWithRot(const InitArg& arg);
    ~AssassinBossIronBallAtkWithRot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    sead::SafeString mCentralAnchorName_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mAddAngle_s{};
};

}  // namespace uking::action
