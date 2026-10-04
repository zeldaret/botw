#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetImpulseDamageMin : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetImpulseDamageMin, ksys::act::ai::Action)
public:
    explicit SetImpulseDamageMin(const InitArg& arg);
    ~SetImpulseDamageMin() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mReactionLevel_s{};
    // static_param at offset 0x28
    const bool* mIsGuardable_s{};
    // static_param at offset 0x30
    const bool* mIsGuarantee_s{};
};

}  // namespace uking::action
