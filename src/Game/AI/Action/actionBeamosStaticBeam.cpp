#include "Game/AI/Action/actionBeamosStaticBeam.h"

namespace uking::action {

BeamosStaticBeam::BeamosStaticBeam(const InitArg& arg) : StopASPlay(arg) {}

BeamosStaticBeam::~BeamosStaticBeam() = default;

bool BeamosStaticBeam::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void BeamosStaticBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
}

void BeamosStaticBeam::leave_() {
    StopASPlay::leave_();
}

void BeamosStaticBeam::loadParams_() {
    StopASPlay::loadParams_();
    getStaticParam(&mBeamRange_s, "BeamRange");
    getStaticParam(&mBeamSpeed_s, "BeamSpeed");
    getStaticParam(&mUseDynamicCutting_s, "UseDynamicCutting");
    getStaticParam(&mBeamBoneName_s, "BeamBoneName");
    getStaticParam(&mBeamActorName_s, "BeamActorName");
    getStaticParam(&mBeamActorKey_s, "BeamActorKey");
    getStaticParam(&mMuzzleOffset_s, "MuzzleOffset");
    getStaticParam(&mBeamDirection_s, "BeamDirection");
    getMapUnitParam(&mBeamRange_m, "BeamRange");
}

void BeamosStaticBeam::calc_() {
    StopASPlay::calc_();
}

}  // namespace uking::action
