#pragma once

#include "Game/AI/Action/actionGuardianMiniWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardWait : public GuardianMiniWait {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardWait, GuardianMiniWait)
public:
    explicit GuardianMiniGuardWait(const InitArg& arg);
    ~GuardianMiniGuardWait() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x90
    sead::SafeString mGuardASName_s{};
};

}  // namespace uking::action
