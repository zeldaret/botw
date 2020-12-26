#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteToTargetSimple : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(IgniteToTargetSimple, OnetimeStopASPlay)
public:
    explicit IgniteToTargetSimple(const InitArg& arg);
    ~IgniteToTargetSimple() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mIgniteSpeed_s{};
    // static_param at offset 0x50
    const float* mOffsetHeight_s{};
    // static_param at offset 0x58
    const bool* mIsConnectChild_s{};
    // static_param at offset 0x60
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mIgniteOffset_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mIgniteRotSpeed_s{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x90
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
};

}  // namespace uking::action
