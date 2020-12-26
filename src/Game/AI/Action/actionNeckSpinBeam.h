#pragma once

#include "Game/AI/Action/actionNeckSpin.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NeckSpinBeam : public NeckSpin {
    SEAD_RTTI_OVERRIDE(NeckSpinBeam, NeckSpin)
public:
    explicit NeckSpinBeam(const InitArg& arg);
    ~NeckSpinBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x68
    const float* mBeamRange_s{};
    // static_param at offset 0x70
    sead::SafeString mBeamBoneName_s{};
    // static_param at offset 0x80
    sead::SafeString mBeamActorKey_s{};
    // static_param at offset 0x90
    sead::SafeString mBeamActorName_s{};
    // static_param at offset 0xa0
    const sead::Vector3f* mMuzzleOffset_s{};
    // static_param at offset 0xa8
    const sead::Vector3f* mBeamDirection_s{};
    // map_unit_param at offset 0xb0
    const float* mBeamRange_m{};
};

}  // namespace uking::action
