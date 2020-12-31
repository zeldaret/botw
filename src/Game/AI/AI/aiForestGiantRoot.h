#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(ForestGiantRoot, EnemyRoot)
public:
    explicit ForestGiantRoot(const InitArg& arg);
    ~ForestGiantRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const bool* mIsDamageToEnemy_s{};
    // aitree_variable at offset 0x220
    bool* mIgnoreGiantArmorCondition_a{};
    // aitree_variable at offset 0x228
    void* mGiantNecklaceUnit_a{};
};

}  // namespace uking::ai
