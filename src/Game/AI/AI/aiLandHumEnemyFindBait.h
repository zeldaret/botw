#pragma once

#include "Game/AI/AI/aiUnarmedEnemySearch.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LandHumEnemyFindBait : public UnarmedEnemySearch {
    SEAD_RTTI_OVERRIDE(LandHumEnemyFindBait, UnarmedEnemySearch)
public:
    explicit LandHumEnemyFindBait(const InitArg& arg);
    ~LandHumEnemyFindBait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mRepathTime_s{};
    // dynamic_param at offset 0x70
    ksys::act::BaseProcLink* mTargetBait_d{};
    // static_param at offset 0x78
    const bool* mIsDropWeapon_s{};
    // static_param at offset 0x80
    const bool* mIsValidForceNeck_s{};
    // dynamic_param at offset 0x88
    bool* mIsNotice_d{};
};

}  // namespace uking::ai
