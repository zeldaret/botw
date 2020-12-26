#pragma once

#include "Game/AI/Action/actionForkSeqNoWeaponAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantDoubleGroundPunch : public ForkSeqNoWeaponAttack {
    SEAD_RTTI_OVERRIDE(GiantDoubleGroundPunch, ForkSeqNoWeaponAttack)
public:
    explicit GiantDoubleGroundPunch(const InitArg& arg);
    ~GiantDoubleGroundPunch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    sead::SafeString mASName_s{};
    // static_param at offset 0xf8
    sead::SafeString mASName2_s{};
    // static_param at offset 0x108
    const float* mRotSpeedMax_s{};
    // dynamic2_param at offset 0x140
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
