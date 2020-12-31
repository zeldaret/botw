#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBattleOnFloorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBattleOnFloorRoot, ksys::act::ai::Ai)
public:
    explicit GanonBattleOnFloorRoot(const InitArg& arg);
    ~GanonBattleOnFloorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFarAttackDist_s{};
    // dynamic_param at offset 0x40
    bool* mIsNoWait_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
