#pragma once

#include "Game/AI/AI/aiGuardianAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianRoot : public GuardianAI {
    SEAD_RTTI_OVERRIDE(GuardianRoot, GuardianAI)
public:
    explicit GuardianRoot(const InitArg& arg);
    ~GuardianRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsSuspended_m{};
    // aitree_variable at offset 0x40
    sead::Vector3f* mForceSetDropPos_a{};
};

}  // namespace uking::ai
