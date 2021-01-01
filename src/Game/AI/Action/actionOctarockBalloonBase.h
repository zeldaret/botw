#pragma once

#include "Game/AI/Action/actionBalloonBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockBalloonBase : public BalloonBase {
    SEAD_RTTI_OVERRIDE(OctarockBalloonBase, BalloonBase)
public:
    explicit OctarockBalloonBase(const InitArg& arg);
    ~OctarockBalloonBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xf0
    const float* mConnectReleaseTimer_s{};
    // static_param at offset 0xf8
    const float* mClampWindForceScale_s{};
    // static_param at offset 0x100
    const float* mReduceVel_s{};
    // dynamic_param at offset 0x108
    sead::SafeString mConnectRigidName_d{};
    // dynamic_param at offset 0x118
    sead::Vector3f* mConnectRigidOffset_d{};
    // dynamic_param at offset 0x120
    ksys::act::BaseProcHandle** mRopeActorHandle_d{};
};

}  // namespace uking::action
