#pragma once

#include "Game/AI/AI/aiWeaponRootAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RodRoot : public WeaponRootAI {
    SEAD_RTTI_OVERRIDE(RodRoot, WeaponRootAI)
public:
    explicit RodRoot(const InitArg& arg);
    ~RodRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0xe8
    void* mMagicCreateUnit_a{};
};

}  // namespace uking::ai
