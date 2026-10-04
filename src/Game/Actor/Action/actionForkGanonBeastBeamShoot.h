#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonBeastBeamShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastBeamShoot, ksys::act::ai::Action)
public:
    explicit ForkGanonBeastBeamShoot(const InitArg& arg);
    ~ForkGanonBeastBeamShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mBeamRange_s{};
    // static_param at offset 0x28
    sead::SafeString mBeamBoneName_s{};
    // static_param at offset 0x38
    sead::SafeString mBeamActorKey_s{};
    // static_param at offset 0x48
    sead::SafeString mBeamActorName_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mMuzzleOffset_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mBeamDir_s{};
};

}  // namespace uking::action
