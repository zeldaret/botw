#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IncredibleAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IncredibleAction, ksys::act::ai::Ai)
public:
    explicit IncredibleAction(const InitArg& arg);
    ~IncredibleAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsInvincible_s{};
    // static_param at offset 0x40
    const bool* mIsUnmoving_s{};
    // static_param at offset 0x48
    const bool* mIsNoCollide_s{};
    // static_param at offset 0x50
    const bool* mIsUseIncredibleActionDCCallback_s{};
};

}  // namespace uking::ai
