#include "Game/Actor/Action/actionBeamNeckSpin.h"

namespace uking::action {

BeamNeckSpin::BeamNeckSpin(const InitArg& arg) : NeckSpin(arg) {}

BeamNeckSpin::~BeamNeckSpin() = default;

bool BeamNeckSpin::init_(sead::Heap* heap) {
    return NeckSpin::init_(heap);
}

void BeamNeckSpin::enter_(ksys::act::ai::InlineParamPack* params) {
    NeckSpin::enter_(params);
}

void BeamNeckSpin::leave_() {
    NeckSpin::leave_();
}

void BeamNeckSpin::loadParams_() {
    NeckSpin::loadParams_();
    getStaticParam(&mBeamRange_s, "BeamRange");
    getStaticParam(&mBeamBoneName_s, "BeamBoneName");
    getStaticParam(&mBeamActorKey_s, "BeamActorKey");
    getStaticParam(&mBeamActorName_s, "BeamActorName");
    getStaticParam(&mMuzzleOffset_s, "MuzzleOffset");
    getStaticParam(&mBeamDirection_s, "BeamDirection");
    getMapUnitParam(&mBeamRange_m, "BeamRange");
}

void BeamNeckSpin::calc_() {
    NeckSpin::calc_();
}

}  // namespace uking::action
