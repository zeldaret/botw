#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniGuardSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardSelect, ksys::act::ai::Ai)
public:
    explicit GuardianMiniGuardSelect(const InitArg& arg);
    ~GuardianMiniGuardSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mASSlotRight_s{};
    // static_param at offset 0x40
    const int* mASSlotLeft_s{};
    // static_param at offset 0x48
    const int* mASSlotBack_s{};
};

}  // namespace uking::ai
