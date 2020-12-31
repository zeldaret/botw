#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MimicEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(MimicEnemyNormal, EnemyNormal)
public:
    explicit MimicEnemyNormal(const InitArg& arg);
    ~MimicEnemyNormal() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3d0
    const float* mPlayerForceFindDist_s{};
    // static_param at offset 0x3d8
    const float* mRideHorseMaskPlayerFindDist_s{};
    // aitree_variable at offset 0x3e0
    bool* mIsStartResetMimicry_a{};
};

}  // namespace uking::ai
