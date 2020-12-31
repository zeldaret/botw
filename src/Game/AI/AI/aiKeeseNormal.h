#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(KeeseNormal, EnemyNormal)
public:
    explicit KeeseNormal(const InitArg& arg);
    ~KeeseNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x3d0
    const float* mRoamHeightFromGlowObj_s{};
    // map_unit_param at offset 0x3d8
    const bool* mIsCreateOnFace_m{};
};

}  // namespace uking::ai
