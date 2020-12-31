#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MasterSwordRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(MasterSwordRoot, WeaponRootAI)
public:
    explicit MasterSwordRoot(const InitArg& arg);
    ~MasterSwordRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0xf0
    void* mMagicCreateUnit_a{};
};

}  // namespace uking::ai
