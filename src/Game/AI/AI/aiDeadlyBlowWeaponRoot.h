#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DeadlyBlowWeaponRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(DeadlyBlowWeaponRoot, WeaponRootAI)
public:
    explicit DeadlyBlowWeaponRoot(const InitArg& arg);
    ~DeadlyBlowWeaponRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
