#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReturnFromReactionSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ReturnFromReactionSelect, ksys::act::ai::Ai)
public:
    explicit ReturnFromReactionSelect(const InitArg& arg);
    ~ReturnFromReactionSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsChangeToNormalByFinish_s{};
    // static_param at offset 0x40
    const bool* mIsEnableRetFromDamage_s{};
    // static_param at offset 0x48
    const bool* mIsEnableRetFromGuard_s{};
    // static_param at offset 0x50
    const bool* mIsEnableRetFromRebound_s{};
};

}  // namespace uking::ai
