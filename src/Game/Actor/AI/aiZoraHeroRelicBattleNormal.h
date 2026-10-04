#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroRelicBattleNormal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroRelicBattleNormal, ksys::act::ai::Ai)
public:
    explicit ZoraHeroRelicBattleNormal(const InitArg& arg);
    ~ZoraHeroRelicBattleNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x50];
    // static_param at offset 0x88
    const float* mWarpDistanceXZ_s{};
    // static_param at offset 0x90
    const float* mNearPlayerDistanceXZ_s{};
};

}  // namespace uking::ai
