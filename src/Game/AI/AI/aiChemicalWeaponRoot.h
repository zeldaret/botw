#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChemicalWeaponRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(ChemicalWeaponRoot, WeaponRootAI)
public:
    explicit ChemicalWeaponRoot(const InitArg& arg);
    ~ChemicalWeaponRoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::ai
