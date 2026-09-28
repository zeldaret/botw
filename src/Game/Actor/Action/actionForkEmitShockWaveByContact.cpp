#include "Game/Actor/Action/actionForkEmitShockWaveByContact.h"

namespace uking::action {

ForkEmitShockWaveByContact::ForkEmitShockWaveByContact(const InitArg& arg)
    : ForkEmitShockWave(arg) {}

ForkEmitShockWaveByContact::~ForkEmitShockWaveByContact() = default;

bool ForkEmitShockWaveByContact::init_(sead::Heap* heap) {
    return ForkEmitShockWave::init_(heap);
}

void ForkEmitShockWaveByContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitShockWave::enter_(params);
}

void ForkEmitShockWaveByContact::leave_() {
    ForkEmitShockWave::leave_();
}

void ForkEmitShockWaveByContact::loadParams_() {
    ForkEmitShockWave::loadParams_();
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkEmitShockWaveByContact::calc_() {
    ForkEmitShockWave::calc_();
}

}  // namespace uking::action
