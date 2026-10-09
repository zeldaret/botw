#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGrabBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGrabBase, ksys::act::ai::Action)
public:
    explicit ForkGrabBase(const InitArg& arg);
    ~ForkGrabBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mGrabIdx_s{};
    // static_param at offset 0x28
    const bool* mIsNoGrabSuccess_s{};
};

}  // namespace uking::action
