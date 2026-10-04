#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossIronBallAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AssassinBossIronBallAttack, ksys::act::ai::Ai)
public:
    explicit AssassinBossIronBallAttack(const InitArg& arg);
    ~AssassinBossIronBallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIronBallNum_s{};
    // static_param at offset 0x40
    sead::SafeString mIronBallPartsName_s{};
};

}  // namespace uking::ai
