#pragma once

#include "Game/AI/AI/aiChemicalWeaponRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordWeapon : public ChemicalWeaponRoot {
    SEAD_RTTI_OVERRIDE(SiteBossSwordWeapon, ChemicalWeaponRoot)
public:
    explicit SiteBossSwordWeapon(const InitArg& arg);
    ~SiteBossSwordWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
