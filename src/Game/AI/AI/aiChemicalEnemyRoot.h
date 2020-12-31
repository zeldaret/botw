#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChemicalEnemyRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(ChemicalEnemyRoot, EnemyRoot)
public:
    explicit ChemicalEnemyRoot(const InitArg& arg);
    ~ChemicalEnemyRoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const bool* mIsElementNoHit_s{};
    // static_param at offset 0x1e0
    const bool* mIsElectricWater_s{};
    // static_param at offset 0x1e8
    sead::SafeString mColorASName_s{};
};

}  // namespace uking::ai
