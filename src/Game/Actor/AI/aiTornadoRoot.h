#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TornadoRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TornadoRoot, ksys::act::ai::Ai)
public:
    explicit TornadoRoot(const InitArg& arg);
    ~TornadoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsHitOnlyPlayer_s{};
    // map_unit_param at offset 0x40
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x48
    const int* mAttackPower_m{};
};

}  // namespace uking::ai
