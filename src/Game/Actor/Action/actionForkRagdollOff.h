#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkRagdollOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkRagdollOff, ksys::act::ai::Action)
public:
    explicit ForkRagdollOff(const InitArg& arg);
    ~ForkRagdollOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mOffTiming_s{};
    // aitree_variable at offset 0x28
    void* mCRBOffsetUnit_a{};
};

}  // namespace uking::action
