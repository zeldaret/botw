#pragma once

#include "Game/AI/Action/actionGetUpLinear.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossGetUpLinear : public GetUpLinear {
    SEAD_RTTI_OVERRIDE(SiteBossGetUpLinear, GetUpLinear)
public:
    explicit SiteBossGetUpLinear(const InitArg& arg);
    ~SiteBossGetUpLinear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x160
    const bool* mIsRestoreRigidBody_s{};
    // static_param at offset 0x168
    const sead::Vector3f* mForceRecoverOffset_s{};
    // static_param at offset 0x170
    const sead::Vector3f* mForceRecoverDist_s{};
};

}  // namespace uking::action
