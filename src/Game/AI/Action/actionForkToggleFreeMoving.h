#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkToggleFreeMoving : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkToggleFreeMoving, ksys::act::ai::Action)
public:
    explicit ForkToggleFreeMoving(const InitArg& arg);
    ~ForkToggleFreeMoving() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mEnterChoice_s{};
    // static_param at offset 0x28
    const int* mLeaveChoice_s{};
};

}  // namespace uking::action
