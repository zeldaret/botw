#include "Game/AI/Action/actionForkEmitShockWaveByContact.h"

namespace uking::action {

ForkEmitShockWaveByContact::ForkEmitShockWaveByContact(const InitArg& arg)
    : ForkASTrgEmitShockWave(arg) {}

ForkEmitShockWaveByContact::~ForkEmitShockWaveByContact() = default;

bool ForkEmitShockWaveByContact::init_(sead::Heap* heap) {
    return ForkASTrgEmitShockWave::init_(heap);
}

void ForkEmitShockWaveByContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgEmitShockWave::enter_(params);
}

void ForkEmitShockWaveByContact::leave_() {
    ForkASTrgEmitShockWave::leave_();
}

void ForkEmitShockWaveByContact::loadParams_() {
    ForkASTrgEmitShockWave::loadParams_();
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkEmitShockWaveByContact::calc_() {
    ForkASTrgEmitShockWave::calc_();
}

}  // namespace uking::action
