#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StopASIgnite : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(StopASIgnite, OnetimeStopASPlay)
public:
    explicit StopASIgnite(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mIgniteSpeed_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mIgniteOffset_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mIgniteVelocityDir_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mIgniteRotate_s{};
    // static_param at offset 0x68
    const sead::Vector3f* mIgniteRotSpeed_s{};
    // dynamic_param at offset 0x70
    ksys::act::BaseProcHandle** mIgniteHandle_d{};
    // aitree_variable at offset 0x78
    void* mGeneratedActorLink_a{};
};

}  // namespace uking::action
