#pragma once

#include "Game/AI/Action/actionForkAlwaysForceGetUp.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysForceGetUpWithOffset : public ForkAlwaysForceGetUp {
    SEAD_RTTI_OVERRIDE(ForkAlwaysForceGetUpWithOffset, ForkAlwaysForceGetUp)
public:
    explicit ForkAlwaysForceGetUpWithOffset(const InitArg& arg);
    ~ForkAlwaysForceGetUpWithOffset() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const sead::Vector3f* mRotCenterPos_s{};
};

}  // namespace uking::action
