#pragma once

#include "Game/AI/Action/actionGuardBreak.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardBreak : public GuardBreak {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardBreak, GuardBreak)
public:
    explicit GuardianMiniGuardBreak(const InitArg& arg);
    ~GuardianMiniGuardBreak() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const int* mASSlot_s{};
    // static_param at offset 0x68
    sead::SafeString mGuardBreakASName_s{};
    // static_param at offset 0x78
    sead::SafeString mOtherASName_s{};
};

}  // namespace uking::action
