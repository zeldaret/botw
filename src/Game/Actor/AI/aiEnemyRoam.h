#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRoam, ksys::act::ai::Ai)
public:
    explicit EnemyRoam(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mSearchPer_s{};
    // static_param at offset 0x40
    const float* mTerritoryRadius_s{};
    // static_param at offset 0x48
    const float* mTerritoryRadiusRnd_s{};
    // static_param at offset 0x50
    const float* mMinMoveDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
