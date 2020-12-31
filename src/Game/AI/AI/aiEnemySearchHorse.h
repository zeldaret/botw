#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemySearchHorse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemySearchHorse, ksys::act::ai::Ai)
public:
    explicit EnemySearchHorse(const InitArg& arg);
    ~EnemySearchHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRepathTime_s{};
    // static_param at offset 0x40
    const float* mSearchDist_s{};
    // static_param at offset 0x48
    const float* mRideRadius_s{};
    // static_param at offset 0x50
    const bool* mNoWeaponRiding_s{};
};

}  // namespace uking::ai
