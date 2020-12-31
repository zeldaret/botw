#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyShieldSearchOrBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyShieldSearchOrBattle, ksys::act::ai::Ai)
public:
    explicit EnemyShieldSearchOrBattle(const InitArg& arg);
    ~EnemyShieldSearchOrBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mShieldIdx_s{};
    // static_param at offset 0x40
    const int* mNoShieldEquipWpIdx_s{};
    // static_param at offset 0x48
    const float* mSearchShieldDist_s{};
    // static_param at offset 0x50
    const float* mNoShieldSearchDist_s{};
    // static_param at offset 0x58
    const float* mNoShieldTargetNearDist_s{};
    // static_param at offset 0x60
    const float* mShieldReachDist_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
