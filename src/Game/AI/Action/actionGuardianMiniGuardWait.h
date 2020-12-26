#pragma once

#include "Game/AI/Action/actionGuardianMiniWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardWait : public GuardianMiniWait {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardWait, GuardianMiniWait)
public:
    explicit GuardianMiniGuardWait(const InitArg& arg);
    ~GuardianMiniGuardWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    sead::SafeString mGuardASName_s{};
};

}  // namespace uking::action
