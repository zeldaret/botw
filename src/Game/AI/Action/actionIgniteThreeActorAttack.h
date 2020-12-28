#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IgniteThreeActorAttack : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(IgniteThreeActorAttack, OnetimeStopASPlay)
public:
    explicit IgniteThreeActorAttack(const InitArg& arg);
    ~IgniteThreeActorAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x48
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcHandle** mIgniteHandle2_d{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcHandle** mIgniteHandle3_d{};
    // static_param at offset 0x60
    sead::SafeString mBaseNode_s{};
    // static_param at offset 0x70
    const float* mIgniteSpeed_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mIgniteOffset_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mIgniteRotSpeed_s{};
};

}  // namespace uking::action
