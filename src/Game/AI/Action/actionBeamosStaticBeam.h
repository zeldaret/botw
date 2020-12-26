#pragma once

#include "Game/AI/Action/actionStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeamosStaticBeam : public StopASPlay {
    SEAD_RTTI_OVERRIDE(BeamosStaticBeam, StopASPlay)
public:
    explicit BeamosStaticBeam(const InitArg& arg);
    ~BeamosStaticBeam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mBeamRange_s{};
    // static_param at offset 0x50
    const float* mBeamSpeed_s{};
    // static_param at offset 0x58
    const bool* mUseDynamicCutting_s{};
    // static_param at offset 0x60
    sead::SafeString mBeamBoneName_s{};
    // static_param at offset 0x70
    sead::SafeString mBeamActorName_s{};
    // static_param at offset 0x80
    sead::SafeString mBeamActorKey_s{};
    // static_param at offset 0x90
    const sead::Vector3f* mMuzzleOffset_s{};
    // static_param at offset 0x98
    const sead::Vector3f* mBeamDirection_s{};
    // map_unit_param at offset 0xa0
    const float* mBeamRange_m{};
};

}  // namespace uking::action
