#include "Game/AI/Action/actionForkGanonBeastBeamShoot.h"

namespace uking::action {

ForkGanonBeastBeamShoot::ForkGanonBeastBeamShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGanonBeastBeamShoot::~ForkGanonBeastBeamShoot() = default;

bool ForkGanonBeastBeamShoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastBeamShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonBeastBeamShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastBeamShoot::loadParams_() {
    getStaticParam(&mBeamRange_s, "BeamRange");
    getStaticParam(&mBeamBoneName_s, "BeamBoneName");
    getStaticParam(&mBeamActorKey_s, "BeamActorKey");
    getStaticParam(&mBeamActorName_s, "BeamActorName");
    getStaticParam(&mMuzzleOffset_s, "MuzzleOffset");
    getStaticParam(&mBeamDir_s, "BeamDir");
}

void ForkGanonBeastBeamShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
