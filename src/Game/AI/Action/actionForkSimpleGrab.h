#pragma once

#include "Game/AI/Action/actionForkSimpleGrabBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSimpleGrab : public ForkSimpleGrabBase {
    SEAD_RTTI_OVERRIDE(ForkSimpleGrab, ForkSimpleGrabBase)
public:
    explicit ForkSimpleGrab(const InitArg& arg);
    ~ForkSimpleGrab() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const float* mCheckRadius_s{};
};

}  // namespace uking::action
