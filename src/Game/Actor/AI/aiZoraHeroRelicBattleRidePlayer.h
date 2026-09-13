#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroRelicBattleRidePlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroRelicBattleRidePlayer, ksys::act::ai::Ai)
public:
    explicit ZoraHeroRelicBattleRidePlayer(const InitArg& arg);
    ~ZoraHeroRelicBattleRidePlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mZoraHeroShowMsgUnit_a{};
};

}  // namespace uking::ai
